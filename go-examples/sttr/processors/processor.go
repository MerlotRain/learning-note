package processors

import (
	"fmt"
	"strconv"
	"strings"

	"github.com/charmbracelet/bubbles/list"
)

var List = []list.Item{
	ASCII85Encoding{},
	ASCII85Decoding{},
}

type Processor interface {
	Name() string

	Alias() []string

	Transform(data []byte, opts ...Flag) (string, error)

	Flags() []Flag

	Title() string

	Description() string

	FilterValue() string
}

type FlagType string

func (f FlagType) String() string {
	return string(f)
}

func (f FlagType) IsString() bool {
	return f == FlagString
}

const (
	FlagInt    = FlagType("Int")
	FlagUint   = FlagType("UInt")
	FlagBool   = FlagType("Bool")
	FlagString = FlagType("String")
)

type Flag struct {
	Name  string
	Short string
	Desc  string
	Type  FlagType
	Value any
}

type Zeropad struct{}

func (p Zeropad) Name() string {
	return "zeropad"
}

func (p Zeropad) Alias() []string {
	return nil
}

func (p Zeropad) Transform(data []byte, opts ...Flag) (string, error) {
	strIn := strings.TrimSpace(string(data))
	neg := ""
	i, err := strconv.ParseFloat(strIn, 64)
	if err != nil {
		return "", fmt.Errorf("number expected: '%s'", data)
	}
	if i < 0 {
		neg = "-"
		data = data[1:]
	}

	var n int
	pre := ""
	for _, flag := range opts {
		switch flag.Short {
		case "n":
			x, ok := flag.Value.(uint)
			if ok {
				n = int(x)
			}
		case "p":
			x, ok := flag.Value.(string)
			if ok {
				pre = x
			}
		}
	}
	return fmt.Sprintf("%s%s%s%s", pre, neg, strings.Repeat("0", n), data), nil
}

func (p Zeropad) Flags() []Flag {
	return []Flag{
		{
			Name:  "number-of-zeros",
			Short: "n",
			Desc:  "Number of zeros to be padded",
			Value: 5,
			Type:  FlagUint,
		},
		{
			Name:  "prefix",
			Short: "p",
			Desc:  "The number get prefixed with this",
			Value: "",
			Type:  FlagString,
		},
	}
}

func (p Zeropad) Title() string {
	title := strings.ToTitle(p.Name())
	return fmt.Sprintf("%s (%s)", title, p.Name())
}

func (p Zeropad) Description() string {
	return "Pad a number with zeros"
}

func (p Zeropad) FilterValue() string {
	return p.Title()
}
