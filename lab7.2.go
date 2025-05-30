package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

func isValInput(val, min, max int) bool {
	return val >= min && val <= max
}

func generatePermutations(nums []int, left int, res *[]string) {
	if left == len(nums) {
		var sb strings.Builder
		for _, num := range nums {
			sb.WriteString(strconv.Itoa(num))
		}
		*res = append(*res, sb.String())
		return
	}

	for i := left; i < len(nums); i++ {
		nums[left], nums[i] = nums[i], nums[left]
		generatePermutations(nums, left+1, res)
		nums[left], nums[i] = nums[i], nums[left]
	}
}

func readInt(prompt string, min, max int) int {
	reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Print(prompt)
		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(input)
		if val, err := strconv.Atoi(input); err == nil && isValInput(val, min, max) {
			return val
		}
		fmt.Println("Некорректный ввод. Повторите попытку.")
	}
}

func main() {
	n := readInt("Введите количество чисел из которых нужно получить перестановки: ", 1, 9)

	fact := 1
	for i := 2; i <= n; i++ {
		fact *= i
	}

	k := readInt("Введите порядковый номер перестановки: ", 1, fact)

	// Инициализация массива
	nums := make([]int, n)
	for i := 0; i < n; i++ {
		nums[i] = i + 1
	}

	var res []string
	generatePermutations(nums, 0, &res)
	sort.Strings(res)

	fmt.Println("Результат:", res[k-1])
}
