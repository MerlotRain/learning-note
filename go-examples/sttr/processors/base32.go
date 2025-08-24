package processors

import (
	"encoding/base32"
	"fmt"
)

type Base32Encoding struct{}

func (p Base32Encoding) Name() string {
	return "base32-encode"
}

func (p Base32Encoding) Alias() []string {
	return []string{"b32-enc", "b32-encode"}
}

func (p Base32Encoding) Transform(data []byte, opts ...Flag) (string, error) {
	return base32.StdEncoding.EncodeToString(data), nil
}

func (p Base32Encoding) Flags() []Flag {
	return nil
}

func (p Base32Encoding) Title() string {
	title := "Base32 Encode"
	return fmt.Sprintf("%s (%s)", title, p.Name())
}

func (p Base32Encoding) Description() string {
	return "Encode your text to Base32"
}

func (p Base32Encoding) FilterValue() string {
	return p.Title()
}

type Base32Decoding struct{}

func (p Base32Decoding) Name() string {
	return "base32-decode"
}

func (p Base32Decoding) Alias() []string {
	return []string{"b32-dec", "b32-decode"}
}

func (p Base32Decoding) Transform(data []byte, opts ...Flag) (string, error) {
	decodedString, err := base32.StdEncoding.DecodeString(string(data))
	return string(decodedString), err
}

func (p Base32Decoding) Flags() []Flag {
	return nil
}

func (p Base32Decoding) Title() string {
	title := "Base32 Decode"
	return fmt.Sprintf("%s (%s)", title, p.Name())
}

func (p Base32Decoding) Description() string {
	return "Decode your base32 text"
}

func (p Base32Decoding) FilterValue() string {
	return p.Title()
}
