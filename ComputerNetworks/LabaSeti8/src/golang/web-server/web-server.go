package main

import (
	"errors"
	"log"
	"net/http"
	"os"
	"os/exec"
	"strings"
)

func main() {
	http.Handle("/", http.FileServer(http.Dir("./static")))
	http.HandleFunc("/golang/", golangHandler)

	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Fatal(err)
	}
	log.Println("Starting http server at port 8080")
}

func golangHandler(w http.ResponseWriter, r *http.Request) {

	name, fullName, err := isJava(r.URL.Path)
	if err != nil {
		return
	}
	var param []string

	split1 := strings.Split(r.URL.RawQuery, "&")
	for _, s := range split1 {
		split2 := strings.Split(s, "=")
		if len(split2) != 2 {
			return
		}
		param = append(param, split2[1])
	}

	_, err = os.Stat("./java/" + fullName)
	if err != nil {
		return
	}

	cmd := exec.Command("javac", "./java/"+fullName)
	cmd.Output()

	args := append(append([]string{}, "-classpath", "./java",
		name), param...)
	cmd = exec.Command(
		"java",
		args...,
	)
	output, err := cmd.Output()
	if err != nil {
		log.Fatal(err)
	}
	w.Write(output)
}

func isJava(path string) (string, string, error) {
	//.java?a=1&b=2&c=3
	str := strings.Split(path, "/")
	if len(str) < 2 {
		return "", "", errors.New("error")
	}
	fullName := str[len(str)-1]
	if fullName == "" {
		return "", "", errors.New("error")
	}
	splitName := strings.Split(fullName, ".")
	if len(splitName) != 2 {
		return "", "", errors.New("error")
	}
	name := splitName[0]
	end := splitName[1]

	if name == "" || end != "java" {
		return "", "", errors.New("error")
	}

	return name, fullName, nil
}
