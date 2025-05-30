package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// Получает максимальную длину перекрытия между суффиксом first и префиксом second
func getOverlap(first, second string) int {
	maxOver := 0
	lenFirst := len(first)
	lenSecond := len(second)

	for i := 1; i <= min(lenFirst, lenSecond); i++ {
		if first[lenFirst-i:] == second[:i] {
			maxOver = i
		}
	}
	return maxOver
}

// Рекурсивно формирует все возможные цепочки слов и выбирает минимальную по длине
func makeCrossword(words []string, used []bool, curr string, minLen *int, bestRes *string, usedCount int, lastWord string) {
	if usedCount == len(words) {
		if len(curr) < *minLen {
			*minLen = len(curr)
			*bestRes = curr
		}
		return
	}

	for i := 0; i < len(words); i++ {
		if !used[i] {
			overlap := getOverlap(lastWord, words[i])

			used[i] = true
			nextWord := words[i]
			oldSize := len(curr)
			curr += nextWord[overlap:]
			makeCrossword(words, used, curr, minLen, bestRes, usedCount+1, words[i])
			curr = curr[:oldSize]
			used[i] = false
		}
	}
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func main() {
	var c int
	fmt.Print("Введите количество слов: ")
	_, err := fmt.Scan(&c)
	if err != nil || c <= 0 {
		fmt.Println("Ошибка. Введите положительное число")
		return
	}

	words := make([]string, c)
	scanner := bufio.NewScanner(os.Stdin)
	fmt.Println("Введите", c, "слов:")

	for i := 0; i < c; i++ {
		if !scanner.Scan() {
			fmt.Println("Ошибка чтения ввода")
			return
		}
		words[i] = strings.TrimSpace(scanner.Text())
		if words[i] == "" {
			fmt.Println("Ошибка: пустое слово невозможно добавить")
			return
		}
	}

	minLen := int(1e9)
	bestRes := ""

	for i := 0; i < c; i++ {
		used := make([]bool, c)
		used[i] = true
		makeCrossword(words, used, words[i], &minLen, &bestRes, 1, words[i])
	}

	fmt.Println("Минимальная длина кроссворда:", minLen)
	fmt.Println("Цепочка:", bestRes)
}
