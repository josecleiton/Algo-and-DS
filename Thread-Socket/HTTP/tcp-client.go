package main
import (
   "fmt"
   "net"
   "log"
   "os"
   "bufio"
   "strings"
)

func main() {
   if len(os.Args) < 2 {
      fmt.Println("usage: [host] [port]")
      os.Exit(1)
   }
   for {
      conn, err := net.Dial("tcp", os.Args[1] + ":" + os.Args[2])
      if err != nil {
         log.Panic(err)
      }
      defer conn.Close()
      fmt.Printf("Insira a rota da página: ")
      reader := bufio.NewReader(os.Stdin)
      text, err := reader.ReadString('\n')

      if err != nil {
         log.Fatal(err)
      }

      if text == "exit" || text == "quit" {
         os.Exit(0)
      }

      fmt.Fprintf(conn, "GET /%s HTTP/1.1\r\n\r\n", text)
      log.Println("Resposta do servidor:")
      scanner := bufio.NewScanner(conn)
      {
         unprintable := true
         content := false
         alert := false
         for scanner.Scan() {
            line := scanner.Text()
            if line == "" {
               content = true
            } else if strings.HasPrefix(line, "Content-Type: text/") {
               unprintable = false
            }
            if ! (content && unprintable) {
               log.Println(line)
            } else if (content && ! alert) {
               log.Println("Conteúdo não imprimível no terminal, tente usando um browser!")
               alert = true
            }
         }
      }
   }
}



