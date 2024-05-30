package main

import (
	"LabaSeti9/middlewares"
	"github.com/gin-gonic/gin"
	"golang.org/x/crypto/ssh"
	"log"
	"net/http"
)

const ip = "151.248.113.144"
const port = "443"
const login = "iu9lab"
const password = "12345678990iu9iu9"

type Message struct {
	Message string `json:"message"`
}

func main() {

	server := gin.New()

	server.Use(middlewares.BasicAuth())

	server.Static("/css", "./templates/css")

	server.LoadHTMLGlob("templates/*.html")

	server.GET("/sin", func(ctx *gin.Context) {
		ctx.HTML(http.StatusOK, "sync.html", nil)
	})

	server.POST("/sin", UsersOnlineHandler2)

	server.GET("/arcsin", func(ctx *gin.Context) {
		ctx.HTML(http.StatusOK, "async.html", nil)
	})

	server.Run(":8099")
}

func UsersOnlineHandler2(ctx *gin.Context) {
	p := ctx.PostForm("command")
	log.Println(p)
	ctx.Writer.Write([]byte(getUserOnline(p).Message))
}

func getUserOnline(reg string) (users Message) {
	users = Message{
		Message: getFilenamesFromResponse(getResponse(reg)),
	}

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
