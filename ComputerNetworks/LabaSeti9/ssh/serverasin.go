package main

import (
	"github.com/gliderlabs/ssh"
	"golang.org/x/crypto/ssh/terminal"
	"golang.org/x/text/encoding/charmap"
	"log"
	"os/exec"
	"runtime"
	"strconv"
	"strings"
)

const port int = 2222

var mapUser = map[string]string{
	"admin":   "admin",
	"arkadiy": "12345",
	"iu9":     "iu9",
}

func main() {
	s := &ssh.Server{
		Addr:            ":" + strconv.Itoa(port),
		Handler:         sessionHandler,
		PasswordHandler: passwordHandler,
	}
	log.Println("Starting ssh " + s.Addr)
	log.Fatal(s.ListenAndServe())
}

func passwordHandler(ctx ssh.Context, pass string) bool {
	for login, password := range mapUser {
		if ctx.User() == login && pass == password {
			return true
		}
	}
	return false
}

func sessionHandler(s ssh.Session) {
	term := terminal.NewTerminal(s, "$ ")
	log.Println("Server started")
	defer log.Println("Server closed")

	if len(s.Command()) != 0 {
		out := executeCommands(strings.Join(s.Command(), " "))
		_, err := term.Write(out)
		if err != nil {
			log.Fatal(err)
		}
		return
	}

	for {
		line, err := term.ReadLine()
		if err != nil {
			break
		}
		if line != "" {
			out := executeCommands(line)
			_, err := term.Write(out)
			if err != nil {
				log.Println(err)
			}
		}
	}
}

func executeCommands(line string) []byte {
	log.Println("Executing: " + line)
	var comm string
	var args []string
	splitted := strings.Split(line, " ")
	if runtime.GOOS == "windows" {
		comm = "cmd"
		args = append(args, "/C")
		args = append(args, splitted...)
	} else {
		comm = splitted[0]
		if len(splitted) > 1 {
			args = append(args, splitted[1:]...)
		}
	}

	cmd := exec.Command(comm, args...)
	out, err := cmd.CombinedOutput()
	if err != nil {
		log.Println(err)
	}

	if runtime.GOOS == "windows" {
		d := charmap.CodePage866.NewDecoder()
		out, err = d.Bytes(out)
	}

	log.Println(string(out))
	return out
}
