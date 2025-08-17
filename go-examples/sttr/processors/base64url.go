package processors

import (
	"encoding/base64"
	"fmt"
)

type Base64URLEncode struct{}

func (p Base64URLEncode) Name() string {
	return "base64url-encode"
}

func (p Base64URLEncode) Alias() []string {
	return []string{"b64url-enc", "b64url-encode"}
}

func (p Base64URLEncode) Transform(data []byte, opts ...Flag) (string, error) {
	if checkBase64RawFlag(opts) {
		return base64.RawURLEncoding.EncodeToString(data), nil
	}
	return base64.URLEncoding.EncodeToString(data), nil
}

func (p Base64URLEncode) Flags() []Flag {
	return []Flag{base64RawFlag}
}

func (p Base64URLEncode) Title() string {
	title := "Base64URL Encode"
	return fmt.Sprintf("%s (%s)", title, p.Name())
}

func (p Base64URLEncode) Description() string {
	return "Encode your text to Base64URL"
}

func (p Base64URLEncode) FilterValue() string {
	return p.Title()
}

type Base64URLDecode struct{}

func (p Base64URLDecode) Name() string {
	return "base64url-decode"
}

func (p Base64URLDecode) Alias() []string {
	return []string{"b64url-dec", "b64url-decode"}
}

func (p Base64URLDecode) Transform(data []byte, opts ...Flag) (string, error) {
	if checkBase64RawFlag(opts) {
		decodedString, err := base64.RawURLEncoding.DecodeString(string(data))
		return string(decodedString), err
	}
	decodedString, err := base64.URLEncoding.DecodeString(string(data))
	return string(decodedString), err
}

func (p Base64URLDecode) Flags() []Flag {
	return []Flag{base64RawFlag}
}

func (p Base64URLDecode) Title() string {
	title := "Base64URL Decode"
	return fmt.Sprintf("%s (%s)", title, p.Name())
}

func (p Base64URLDecode) Description() string {
	return "Decode your Base64URL text"
}

func (p Base64URLDecode) FilterValue() string {
	return p.Title()
}
