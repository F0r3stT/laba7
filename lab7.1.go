package main

import (
	"fmt"
	"os"

	"github.com/faiface/pixel"
	"github.com/faiface/pixel/imdraw"
	"github.com/faiface/pixel/pixelgl"
	"golang.org/x/image/colornames"
)

type Point struct {
	x, y float64
}

// Рекурсивная функция отрисовки треугольника Серпинского
func drawSierpinski(imd *imdraw.IMDraw, a, b, c Point, depth int) {
	if depth == 0 {
		imd.Color = colornames.White
		imd.Push(
			pixel.V(a.x, a.y),
			pixel.V(b.x, b.y),
			pixel.V(c.x, c.y),
		)
		imd.Polygon(0) // 0 — для заливки (залитый треугольник)
		return
	}

	// Средние точки сторон
	ab := Point{(a.x + b.x) / 2, (a.y + b.y) / 2}
	bc := Point{(b.x + c.x) / 2, (b.y + c.y) / 2}
	ca := Point{(c.x + a.x) / 2, (c.y + a.y) / 2}

	// Рекурсивные вызовы
	drawSierpinski(imd, a, ab, ca, depth-1)
	drawSierpinski(imd, ab, b, bc, depth-1)
	drawSierpinski(imd, ca, bc, c, depth-1)
}

func run() {
	var depth int
	fmt.Print("Введите глубину рекурсии (0-10): ")
	fmt.Scan(&depth)
	if depth < 0 || depth > 10 {
		fmt.Println("Ошибка: глубина должна быть от 0 до 10")
		os.Exit(1)
	}

	cfg := pixelgl.WindowConfig{
		Title:  "Треугольник Серпинского",
		Bounds: pixel.R(0, 0, 900, 700),
		VSync:  true,
	}
	win, err := pixelgl.NewWindow(cfg)
	if err != nil {
		panic(err)
	}

	// Исходные точки большого треугольника
	top := Point{450, 650}
	left := Point{100, 50}
	right := Point{800, 50}

	for !win.Closed() {
		win.Clear(colornames.Black)

		imd := imdraw.New(nil)
		drawSierpinski(imd, top, left, right, depth)
		imd.Draw(win)

		win.Update()
	}
}

func main() {
	pixelgl.Run(run)
}
