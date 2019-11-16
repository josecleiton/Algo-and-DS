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
   fmt.Println("Iniciando servidor...")
   li, err := net.Listen("tcp", ":8082")
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
   fmt.Printf("Lendo a requisição da conexão #%d\n", clientNumber)
   request(conn)
   fmt.Printf("Respondendo a requisição da conexão #%d\n", clientNumber)
}

func request(conn net.Conn) {
   i := 0
   scanner := bufio.NewScanner(conn)
   for scanner.Scan() {
      line := scanner.Text()
      fmt.Println(line)
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
   path = path[1:]
   if path == "" {
      path = "index.html"
   } else {
      fileInfo, err := os.Stat(path)
      if err != nil {
         return make([]byte, 0), ""
      }
      if fileInfo.IsDir() {
         path += "/index.html"
      }
   }

   fmt.Println("Caminho:", path)
   mime := mime.TypeByExtension(filepath.Ext(path))
   fmt.Println("Mime:",mime)
   data, err := ioutil.ReadFile(path)
   if err != nil {
      return make([]byte, 0), ""
   }
   return data, mime
}

func writeError(conn net.Conn, errorCode int) {
   errorString := "HTTP/1.1 "
   if errorCode == 500 {
      errorString += "500 Internal Server Error"
   } else if errorCode == 404 {
      errorString += "404 Not Found"
   }
   errorString += "\r\n\r\n"
   fmt.Fprint(conn, errorString)
}
