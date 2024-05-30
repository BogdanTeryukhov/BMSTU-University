package main

import (
	"bufio"
	"bytes"
	"fmt"
	"github.com/jlaffaye/ftp"
	"log"
	"os"
	"strings"
	"time"
)

//const ftp_host = "students.yss.su"
//const port = "21"
//const login = "ftpiu8"
//const passwd = "3Ru7yOTA"

const ftp_host = "127.0.0.1"
const port = "2001"
const login = "admin"
const passwd = "123456"

var currentCommands = map[string]string{
	"uploadFileJava": "загрузка java файла",
	"deleteFileJava": "удаление java файла",
	"uploadFile":     "загрузка файла",
	"deleteFile":     "удаление файла",
	"exit":           "завершение работы",
	"help":           "список доступных команд",
}

func main() {
	log.Println("Подключение к серверу " + ftp_host + ":" + port)
	c, err := ftp.Dial(ftp_host+":"+port, ftp.DialWithTimeout(5*time.Second))
	if err != nil {
		log.Fatal(err)
	}
	log.Println("Подключение успешно")

	log.Println("Вход в систему")
	err = c.Login(login, passwd)
	if err != nil {
		log.Fatal(err)
	}
	log.Println("Вход одобрен")

	var exit = true
	var scanner = bufio.NewScanner(os.Stdin)
	for exit {
		var line string
		var comm string
		var args []string

		fmt.Print("$ ")
		scanner.Scan()
		line = scanner.Text()

		splitted := strings.Split(line, " ")
		if len(splitted) == 0 {
			log.Println("null split")
			continue
		}

		comm = splitted[0]
		if len(splitted) > 1 {
			args = append(args, splitted[1:]...)
		}

		exit = switchCommands(comm, args, c)
	}

	if err := c.Quit(); err != nil {
		log.Fatal(err)
	}
}

func switchCommands(comm string, args []string, c *ftp.ServerConn) bool {
	switch comm {
	case "uploadFileJava":
		if len(args) == 1 {
			uploadFileJava(args[0], c)
		} else {
			log.Println("Неправильное количество аргументов")
		}
	case "deleteFileJava":
		if len(args) == 1 {
			deleteFileJava(args[0], c)
		} else {
			log.Println("Неправильное количество аргументов")
		}
	case "uploadFile":
		if len(args) == 1 {
			uploadFile(args[0], c)
		} else {
			log.Println("Неправильное количество аргументов")
		}
	case "deleteFile":
		if len(args) == 1 {
			deleteFile(args[0], c)
		} else {
			log.Println("Неправильное количество аргументов")
		}
	case "exit":
		return false
	case "help":
		fmt.Println("Вам доступны следующие команды:")
		for command, value := range currentCommands {
			fmt.Println("    " + command + " - " + value)
		}
	default:
		println("Команды: " + comm + " не существует." +
			"Введите 'help' для получения актуальных команд")
	}
	return true
}

func uploadFileJava(fileName string, c *ftp.ServerConn) {
	log.Println("Загрузка файла " + fileName)
	file, err := os.ReadFile(fileName)
	if err != nil {
		log.Println(err)
	}
	data := bytes.NewBuffer(file)

	split := strings.Split(fileName, "/")
	fileNameShort := split[len(split)-1]

	err = c.Stor("java/"+fileNameShort, data)
	if err != nil {
		log.Println(err)
	}
	log.Println("Java Файл " + fileName + " успешно загружен")
}

func uploadFile(fileName string, c *ftp.ServerConn) {
	log.Println("Загрузка файла " + fileName)
	file, err := os.ReadFile(fileName)
	if err != nil {
		log.Println(err)
	}
	data := bytes.NewBuffer(file)

	split := strings.Split(fileName, "/")
	fileNameShort := split[len(split)-1]

	err = c.Stor("static/"+fileNameShort, data)
	if err != nil {
		log.Println(err)
	}
	log.Println("Java Файл " + fileName + " успешно загружен")
}

func deleteFileJava(fileName string, c *ftp.ServerConn) {
	log.Println("Удаление файла " + fileName)
	split := strings.Split(fileName, "/")
	fileNameShort := split[len(split)-1]

	err := c.Delete("java/" + fileNameShort)

	if err != nil {
		log.Println(err)
	}
	log.Println("Java Файл " + fileNameShort + " успешно удалён")
}

func deleteFile(fileName string, c *ftp.ServerConn) {
	log.Println("Удаление файла " + fileName)
	split := strings.Split(fileName, "/")
	fileNameShort := split[len(split)-1]

	err := c.Delete("static/" + fileNameShort)

	if err != nil {
		log.Println(err)
	}
	log.Println("Java Файл " + fileNameShort + " успешно удалён")
}
