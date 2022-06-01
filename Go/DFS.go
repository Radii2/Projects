package main

import (
	"fmt"
	"os"
	"os/exec"
	"strings"
	"time"
)

//struktura krawędzi, gdzie in - wierzchołek początkowy, out - wierzchołek końcowy
type edge struct {
	in  string
	out string
}

//struktura wierzchołka, gdzie char- nazwa/litera/symbol wierzchołka, links - tablica krawędzi
type vertex struct {
	char  string
	links []edge
}

//mapa oznaczeń cyfrowych wierzchołków
var numbers = make(map[string]int)

//deklaracja grafu oraz tablicę jego wygląda w terminalu i sprawdzenie czy graf jest spójny
func main() {
	graph := make([]vertex, 16)
	cohesion := true
	graph[0] = vertex{char: "a", links: []edge{{in: "a", out: "b"}, {in: "a", out: "f"}}}
	graph[1] = vertex{char: "b", links: []edge{{in: "b", out: "a"}, {in: "b", out: "c"}, {in: "b", out: "g"}}}
	graph[2] = vertex{char: "c", links: []edge{{in: "c", out: "b"}, {in: "c", out: "d"}, {in: "c", out: "h"}}}
	graph[3] = vertex{char: "d", links: []edge{{in: "d", out: "c"}, {in: "d", out: "e"}, {in: "d", out: "l"}}}
	graph[4] = vertex{char: "e", links: []edge{{in: "e", out: "d"}}}
	graph[5] = vertex{char: "f", links: []edge{{in: "f", out: "a"}, {in: "f", out: "g"}, {in: "f", out: "i"}}}
	graph[6] = vertex{char: "g", links: []edge{{in: "g", out: "b"}, {in: "g", out: "f"}, {in: "g", out: "h"}, {in: "g", out: "j"}}}
	graph[7] = vertex{char: "h", links: []edge{{in: "h", out: "c"}, {in: "h", out: "g"}, {in: "h", out: "k"}}}
	graph[8] = vertex{char: "i", links: []edge{{in: "i", out: "f"}, {in: "i", out: "j"}}}
	graph[9] = vertex{char: "j", links: []edge{{in: "j", out: "g"}, {in: "j", out: "i"}, {in: "j", out: "k"}}}
	graph[10] = vertex{char: "k", links: []edge{{in: "k", out: "h"}, {in: "k", out: "j"}}}
	graph[11] = vertex{char: "l", links: []edge{{in: "l", out: "d"}, {in: "l", out: "m"}}}
	graph[12] = vertex{char: "m", links: []edge{{in: "m", out: "l"}}}
	graph[13] = vertex{char: "n", links: []edge{{in: "n", out: "o"}}}
	graph[14] = vertex{char: "o", links: []edge{{in: "o", out: "n"}}}
	graph[15] = vertex{char: "u", links: []edge{}}
	look := [][]string{
		{"a", "-", "-", "b", "-", "-", "c", "-", "-", "d", "-", "-", "e", " ", " ", "u"},
		{"|", " ", " ", "|", " ", " ", "|", " ", " ", "|", " ", " ", " ", " ", " ", " "},
		{"|", " ", " ", "|", " ", " ", "|", " ", " ", "|", " ", " ", " ", " ", " ", " "},
		{"f", "-", "-", "g", "-", "-", "h", " ", " ", "l", "-", "-", "m", " ", " ", "n"},
		{"|", " ", " ", "|", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|"},
		{"|", " ", " ", "|", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|"},
		{"i", "-", "-", "j", "-", "-", "k", " ", " ", " ", " ", " ", " ", " ", " ", "o"},
	}

	for i := 0; i < len(graph); i++ {
		numbers[graph[i].char] = i
	}
	stos := make([]string, 0)
	stos, cohesion = search(graph, cohesion)
	program(look, stos)
	if cohesion == true {
		fmt.Println("Graf jest spójny.")
	} else {
		fmt.Println("Graf nie jest spójny.")
	}
}

// TWORZENIE STOSU//

/*
Funkcja tworzy stos, element - liczba wierzchołków aktualnie zawartych w stosie, chapter - licznik elementów stosu, current - aktualny przeszukiwany wierzchołek
(jego numer w grafie). Pętla wykonuje się do czasu aż wszystkie elementy grafu nie zostaną zawarte w stosie. Podpętla (pętla z j) sprawdza czy
znaleziony końcowy wierzchołek z krawędzi jest już w stosie jeśli jest to szukaj dalej, a jeśli się to go dodaj i przechodzi do tego wierzchołka, którego dodał.
Jeśli znajdzie wszystkie to do stosu dodaje po kolei elementy usuwając ostatni wierzchołek. Funkcja sprawdza też czy stos jest spójny.
*/
func search(graph []vertex, cohesion bool) ([]string, bool) {
	stos := make([]string, 1)
	stos[0] = graph[0].char
	element := 1
	chapter := 0
	current := 0
	for element != len(graph) {
		for j := 0; j < len(graph[current].links); j++ {
			if strings.Contains(stos[chapter], graph[current].links[j].out) == false {
				if check(stos, graph[current].links[j].out) == false {
					stos = append(stos, stos[chapter]+graph[current].links[j].out)
					element += 1
					chapter += 1
					current = find_vertex(graph[current].links[j].out)
					j = 0
				}
			}
		}
		stos = append(stos, strings.Replace(stos[chapter], stos[chapter][len(stos[chapter])-1:], "", 1))
		chapter += 1
		if stos[chapter] == "" && element != len(graph) {
			cohesion = false
			new_start := new_search(graph, stos)
			stos = append(stos, new_start)
			element++
			current = find_vertex(new_start)
			chapter++
		} else {
			current = find_vertex(stos[chapter][len(stos[chapter])-1:])
		}

	}
	for {
		if stos[chapter] == "" {
			stos[chapter] = "-"
			break
		} else {
			stos = append(stos, strings.Replace(stos[chapter], stos[chapter][len(stos[chapter])-1:], "", 1))
			chapter++
		}
	}
	return stos, cohesion
}

//funkcja sprawdza czy kiedykolwiek wierzchołek pojawił się w stosie
func check(stos []string, char string) bool {
	for i := 0; i < len(stos)-1; i++ {
		if strings.Contains(stos[i], char) {
			return true
		}
	}
	return false
}

//szuka numer wierzchołka z grafu, który jest ostatnim ze stosu
func find_vertex(char string) int {
	number := 0
	for i, v := range numbers {
		if char == i {
			number = v
			break
		}
	}
	return number
}

//szuka nowego pierwszego wierzchołka stosu
func new_search(graph []vertex, stos []string) string {
	number := 0
	for i := 0; i < len(graph); i++ {
		if check(stos, graph[i].char) == false {
			number = i
			break
		}
	}
	return graph[number].char
}

//funkcja wywołująca kolejne etapy/elementy stosu
func program(look [][]string, stos []string) {

	position := 0
	last_position := ""
	for position < len(stos) {
		if stos[position] == "-" {
			read(stos[position], look)
			position += 1
		} else if len(stos[position]) == 0 {
			read(stos[position], look)
			last_position = stos[position]
			position += 1
		} else if len(stos[position]) == 1 && len(last_position) == 0 {
			last_position = stos[position]
			look, last_position = path(look, stos, last_position, "", position)
			position += 1
		} else {
			look, last_position = path(look, stos, stos[position], last_position, position)
			position += 1
		}
	}
}

/*
tworzenie ścieżki w terminalu, gdzie stos_position - aktualny etap stosu, last_position - poprzedni etap stosu.
Funkcja przeszukuje tabele z wyglądem grafu, by znaleźć położenie dwóch wierzchołków, a następnie za pomocą funkcji move tworzy tabelę z ruchami i za
pomocą nich porusza się po tabeli look (wygląd grafu w terminalu) zmieniając poszczególne elementy tworząc ścieżkę.
*/
func path(look [][]string, stos []string, stos_position string, last_position string, position int) ([][]string, string) {
	var start, end [2]int
	var start_position string
	changed, finded := false, false
	var moves []string
	nextmove := 0
	if last_position != "" {
		start_position = last_position[len(last_position)-1:]
	}
	final_position := stos_position[len(stos_position)-1:]
	if last_position == "" {
		point1 := false
		for i := range look {
			for j := range look[i] {
				if strings.ToLower(look[i][j]) == final_position {
					start[0] = i
					start[1] = j
					point1 = true
				}
			}
			if point1 == true {
				break
			}
		}
	} else {
		if final_position == start_position {
			point1, point2 := false, false
			for i := range look {
				for j := range look[i] {
					if strings.ToLower(look[i][j]) == start_position {
						start[0] = i
						start[1] = j
						point1 = true
					}
					if strings.ToLower(look[i][j]) == final_position {
						end[0] = i
						end[1] = j
						point2 = true
					}
				}
				if point1 == true && point2 == true {
					break
				}
			}
		} else {
			point1, point2 := false, false
			for i := range look {
				for j := range look[i] {
					if strings.ToLower(look[i][j]) == start_position {
						start[0] = i
						start[1] = j
						point1 = true
					}
					if strings.ToLower(look[i][j]) == final_position {
						end[0] = i
						end[1] = j
						point2 = true
					}
				}
				if point1 == true && point2 == true {
					break
				}
			}
		}
	}
	if last_position != "" {
		moves = move(start, end)
	}
	look[start[0]][start[1]] = strings.ToUpper(look[start[0]][start[1]])
	for finded != true {
		if last_position == "" {
			if final_position != "a" && stos[position+1] == "" {
				read(stos_position, look)
				look[start[0]][start[1]] = strings.ToLower(look[start[0]][start[1]])
			}
			finded = true
		} else {
			if changed == false {
				if len(stos_position) < len(last_position) {
					look[start[0]][start[1]] = strings.ToLower(look[start[0]][start[1]])
				}
				changed = true
				switch moves[nextmove] {
				case "up":
					start[0] -= 1
				case "down":
					start[0] += 1
				case "left":
					start[1] -= 1
				case "right":
					start[1] += 1
				}
			} else {
				if strings.ToLower(look[start[0]][start[1]]) == final_position {
					look[start[0]][start[1]] = strings.ToUpper(look[start[0]][start[1]])
					finded = true
				} else {
					switch moves[nextmove] {
					case "up":
						if look[start[0]][start[1]] == "X" {
							look[start[0]][start[1]] = "|"
							start[0] -= 1
						} else {
							look[start[0]][start[1]] = "X"
							start[0] -= 1
						}
					case "down":
						if look[start[0]][start[1]] == "X" {
							look[start[0]][start[1]] = "|"
							start[0] += 1
						} else {
							look[start[0]][start[1]] = "X"
							start[0] += 1
						}
					case "left":
						if look[start[0]][start[1]] == "x" {
							look[start[0]][start[1]] = "-"
							start[1] -= 1
						} else {
							look[start[0]][start[1]] = "x"
							start[1] -= 1
						}
					case "right":
						if look[start[0]][start[1]] == "x" {
							look[start[0]][start[1]] = "-"
							start[1] += 1
						} else {
							look[start[0]][start[1]] = "x"
							start[1] += 1
						}
					}
					nextmove++
				}
			}
		}
		read(stos_position, look)
	}
	if stos[position+1] == "" || stos[position+1] == "-" {
		look[start[0]][start[1]] = strings.ToLower(look[start[0]][start[1]])
	}
	last_position = stos_position
	return look, last_position
}

//Tworzy tabelę zawierająca ruchy, którymi ścieżka ma się kierować
func move(start [2]int, end [2]int) []string {
	moves := make([]string, 0)
	for start[0] != end[0] || start[1] != end[1] {
		if start[0] == end[0] {
			if start[1] < end[1] {
				moves = append(moves, "right")
				start[1] += 1
			} else {
				moves = append(moves, "left")
				start[1] -= 1
			}
		}
		if start[1] == end[1] {
			if start[0] < end[0] {
				moves = append(moves, "down")
				start[0] += 1
			} else {
				moves = append(moves, "up")
				start[0] -= 1
			}
		}
	}
	return moves
}

//czyszczenie terminalu oraz opóźnienie odczytu
func system() {
	time.Sleep(1 * time.Second)
	cmd := exec.Command("cmd", "/c", "cls")
	cmd.Stdout = os.Stdout
	cmd.Run()
}

//wypisanie aktualnego etapu w stosie oraz wypisanie graf
func read(stos_position string, look [][]string) {

	fmt.Println("STOS:", stos_position)
	for x := range look {
		for y := range look[x] {
			fmt.Printf("%s", look[x][y])
		}
		fmt.Println()
	}
	system()
}
