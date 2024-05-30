package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
	"github.com/gorilla/websocket"
	"golang.org/x/crypto/ssh"
	"log"
	"net/http"
	"strings"
)

const ip = "151.248.113.144"
const port = "443"
const login = "iu9lab"
const password = "12345678990iu9iu9"

type Message struct {
	Message string `json:"message"`
}

var upgrader = websocket.Upgrader{
	CheckOrigin: func(r *http.Request) bool {
		return true
	},
}

func main() {

	server := gin.New()

	server.GET("/", UsersOnlineHandler)

	err := server.Run(":8090")
	if err != nil {
		log.Fatalln(err)
	}
}

func UsersOnlineHandler(ctx *gin.Context) {
	ws, err := upgrader.Upgrade(ctx.Writer, ctx.Request, nil)
	if err != nil {
		fmt.Println(err)
		return
	}

	defer ws.Close()
	for {
		_, p, err := ws.ReadMessage()
		str := string(p)
		res := strings.Split(strings.Split(str, ":")[1], "\"")[1]
		log.Println(res)
		if err != nil {
			return
		}
		err = ws.WriteJSON(getUserOnline(res))
		if err != nil {
			fmt.Println(err)
			break
		}

	}
}

func getUserOnline(reg string) (users Message) {
	users = Message{
		Message: getFilenamesFromResponse(getResponse(reg)),
	}

	return
}

func getFile() (res string) {
	config := &ssh.ClientConfig{
		User: login,
		Auth: []ssh.AuthMethod{
			ssh.Password(password),
		},
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
	}
	client, err := ssh.Dial("tcp", ip+":"+port, config)
	if err != nil {
		log.Fatal(err)
	}
	defer func(client *ssh.Client) {
		err := client.Close()
		if err != nil {

		}
	}(client)
	sess, err := client.NewSession()
	if err != nil {
		log.Fatal(err)
	}
	defer func(sess *ssh.Session) {
		err := sess.Close()
		if err != nil {
		}
	}(sess)

	output, err := sess.Output("cat achtung.txt")
	if err != nil {
		log.Println(err)
	}
	res = string(output)
	return
}

func getResponse(reg string) (response string) {
	config := &ssh.ClientConfig{
		User: login,
		Auth: []ssh.AuthMethod{
			ssh.Password(password),
		},
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
	}
	client, err := ssh.Dial("tcp", ip+":"+port, config)
	if err != nil {
		log.Fatal(err)
	}
	defer func(client *ssh.Client) {
		err := client.Close()
		if err != nil {

		}
	}(client)
	sess, err := client.NewSession()
	if err != nil {
		log.Fatal(err)
	}
	defer func(sess *ssh.Session) {
		err := sess.Close()
		if err != nil {
		}
	}(sess)

	output, err := sess.Output(reg)
	if err != nil {
		log.Println(err)
	}
	response = string(output)
	return
}

func getFilenamesFromResponse(str string) (res string) {
	res = str
	return
}
