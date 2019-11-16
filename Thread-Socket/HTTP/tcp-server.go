package main

import "fmt"
import "log"
import "net"
import "bufio"
import "time"
import "strings"
import "io/ioutil"
import "os"
import "mime"
import "path/filepath"

func main() {
   port := ":8080"
   log.Println("Args", os.Args)
   if len(os.Args) > 1 {
      port = ":" + os.Args[1]
   }
   log.Printf("Iniciando servidor http na porta %s...\n", port)
   li, err := net.Listen("tcp", port)
   if err != nil {
      log.Panic(err)
   }
   defer li.Close()
   i := 1
   for {
      conn, err := li.Accept()
      if err != nil {
         log.Println(err)
      }
      go handle(conn, i)
      i+=1
   }

}

func handle(conn net.Conn, clientNumber int) {
   err := conn.SetDeadline(time.Now().Add(10 * time.Second))
   if err != nil {
      log.Println("CONN TIMEOUT")

   }
   defer conn.Close()
   log.Println("")
   log.Printf("Lendo a requisição da conexão #%d:\n", clientNumber)
   request(conn)
   log.Printf("Enviando resposta a conexão #%d...\n", clientNumber)
}

func request(conn net.Conn) {
   i := 0
   scanner := bufio.NewScanner(conn)
   for scanner.Scan() {
      line := scanner.Text()
      log.Println(line)
      if i == 0 {
         tokens := strings.Fields(line)
         if  tokens[0] != "GET" {
            writeError(conn, 500)
            break
         }
         file, mime := getFileByRoute(tokens[1])
         if mime == "" {
            writeError(conn, 404)
            break
         } else {
            defer response(conn, file, mime)
         }
      }
      if line == "" {
         break
      }
      i++
   }
}

func response(conn net.Conn, content []byte, mime string) {
   fmt.Fprint(conn, "HTTP/1.1 200 OK\r\n")
   fmt.Fprintf(conn, "Content-Length: %d\r\n", len(content))
   fmt.Fprintf(conn, "Content-Type: %s\r\n", mime)
   fmt.Fprint(conn, "\r\n")
   fmt.Fprint(conn, string(content))
}

func getFileByRoute(path string) ([]byte, string){
   dirPath := ""
   path = path[1:]
   if path == "" {
      path = "index.html"
   } else {
      fileInfo, err := os.Stat(path)
      if err != nil {
         return make([]byte, 0), ""
      }
      if fileInfo.IsDir() {
         dirPath = filepath.Base(path)
         path += "/index.html"
      }
   }

   log.Println("Caminho:", path)
   mime := mime.TypeByExtension(filepath.Ext(path))
   log.Println("Mime:",mime)
   data, err := ioutil.ReadFile(path)
   if err != nil && dirPath == "" {
      return make([]byte, 0), ""
   } else if dirPath != "" {
      files, _ := ioutil.ReadDir(dirPath)
      // fmt.Println("dirPath:",dirPath)
      htmlDirPage := fmt.Sprintf("<html><head><title>%s</title></head><body><h1>Directory: /%s</h1><ul>", dirPath, dirPath)
      for _, f := range files {
         fullpath := dirPath + "/" + f.Name()
         log.Println("fullpath:", fullpath)
         htmlDirPage += fmt.Sprintf("<li><a href=\"%s\">%s</a></li>", fullpath ,f.Name())
      }
      htmlDirPage += "</ul></body></html>"
      data = []byte(htmlDirPage)
   }
   return data, mime
}

func writeError(conn net.Conn, errorCode int) {
   errorString := "HTTP/1.1 "
   if errorCode == 404 {
      errorString += "404 Not Found"
   } else {
      errorString += "500 Internal Server Error"
   }
   errorString += "\r\n\r\n"
   fmt.Fprint(conn, errorString)
}
