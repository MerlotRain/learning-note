package ui

import (
	"fmt"
	"log"
	"os"

	"github.com/charmbracelet/lipgloss"

	"github.com/charmbracelet/bubbles/list"
	tea "github.com/charmbracelet/bubbletea"
	"github.com/merlotrain/rttr/processors"
	"github.com/merlotrain/rttr/utils"
	"golang.org/x/term"
)

var (
	maxWidth     = 72
	appStyle     = lipgloss.NewStyle().MaxWidth(maxWidth)
	borderStyle  = lipgloss.AdaptiveColor{Light: "#874BFD", Dark: "#7D56F4"}
	specialStyle = lipgloss.AdaptiveColor{Light: "#43BF6D", Dark: "#73F59F"}
)

type UI struct {
	list              list.Model
	input             string
	quitting          bool
	selectedProcessor processors.Processor
}

func New(input string) UI {
	return UI{
		input: input,
	}
}

func (u *UI) Render() {
	termWidth, _, err := term.GetSize(int(os.Stdout.Fd()))
	if err != nil || termWidth > maxWidth {
		termWidth = maxWidth
	}

	if u.input == "" {
		divider := lipgloss.NewStyle().Margin(0, 1).Foreground(borderStyle).Render("·")
		info := lipgloss.NewStyle().Foreground(specialStyle).Render("[ Enter 2 empty lines to process ]")

		title := lipgloss.NewStyle().
			MaxWidth(termWidth).
			BorderStyle(lipgloss.NormalBorder()).
			BorderTop(true).BorderBottom(true).BorderForeground(borderStyle).Render("Previde string to transform" + divider + info)

		fmt.Println(appStyle.Render(title))
		u.input = utils.ReadMultilineInput()
	}

	u.list = list.New(processors.List, list.NewDefaultDelegate(), 0, 0)
	u.list.Title = "Select transformation"

	if _, err := tea.NewProgram(u, tea.WithAltScreen()).Run(); err != nil {
		log.Fatalf("error running ui: %v", err)
	}

	if u.selectedProcessor != nil {
		data, err := u.selectedProcessor.Transform([]byte(u.input))
		if err != nil {
			data = fmt.Sprintf("error: %s", err.Error())
		}

		border := lipgloss.NewStyle().Width(termWidth).BorderTop(true).BorderStyle(lipgloss.NormalBorder()).BorderForeground(borderStyle).String()

		fmt.Println(border)
		fmt.Println(data)
	}
}

func (u *UI) Init() tea.Cmd {
	return nil
}

func (u *UI) View() string {
	if u.quitting {
		return ""
	}
	return appStyle.Render(u.list.View())
}

func (u *UI) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
	switch msg := msg.(type) {
	case tea.KeyMsg:
		if u.list.FilterState() == list.Filtering {
			break
		}
		switch keypress := msg.String(); keypress {
		case "q", "ctrl+c":
			u.quitting = true
			return u, tea.Quit
		case "enter":
			u.selectedProcessor = u.list.SelectedItem().(processors.Processor)
			u.quitting = true
			return u, tea.Quit
		}
	case tea.WindowSizeMsg:
		h, w := appStyle.GetFrameSize()
		u.list.SetSize(msg.Width-h, msg.Height-w)
	}

	var cmd tea.Cmd
	u.list, cmd = u.list.Update(msg)
	return u, cmd
}
