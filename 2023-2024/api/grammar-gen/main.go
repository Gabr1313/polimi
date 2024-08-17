package main

import (
	"fmt"
	"os"
	"strings"
	"sync"
	"unicode"
)

var m map[string]bool
var mut sync.Mutex
var subs [][2]string
var wg sync.WaitGroup

// @perf would be better to use a trie or Z-algorithm

func main() {
	file_name := "in.txt"
	if len(os.Args) > 1 {
		file_name = os.Args[1]
	}
	data, err := os.ReadFile(file_name)
	check(err)
	content := string(data[:])
	lines := strings.Split(content, "\n")
	s := lines[0]
	for _, l := range lines[1:] {
		w := strings.Split(l, " ")
		if len(w) < 2 { // ugly
			if len(w) == 1 {
				subs = append(subs, [2]string{w[0], ""})
			} else {
				continue
			}
		}
		fmt.Println(w)
		subs = append(subs, [2]string{w[0], w[1]})
	}
	fmt.Println("")
	m = make(map[string]bool)
	recurse([]string{s})
	wg.Wait()
}

func recurse(s []string) {
	wg.Add(1)
	go func() {
		defer wg.Done()
		last := s[len(s)-1]
		if len(last) > 100 {
			return
		}

		mut.Lock()
		if _, ok := m[last]; ok {
			mut.Unlock()
			return
		}
		m[last] = true
		mut.Unlock()

		if isLowercase(last) {
			fmt.Println(len(s[len(s)-1]))
			fmt.Println(s)
			return
		}
		// fmt.Println(s)

		for _, pair := range subs {
			for j := 0; ; j++ {
				idx := strings.Index(last[j:], pair[0])
				if idx == -1 {
					break
				}
				j = j + idx
				s_2 := make([]string, len(s))
				copy(s_2, s) // @perf... AHAHHA
				recurse(append(s_2, last[:j]+pair[1]+last[j+len(pair[0]):]))
			}
		}
	}()
}

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func isLowercase(s string) bool {
	for _, char := range s {
		if !unicode.IsLower(char) {
			return false
		}
	}
	return true
}
