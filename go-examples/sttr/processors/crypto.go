package processors

import (
	"crypto/md5"
	"encoding/hex"
	"fmt"
)

type MD5 struct{}

func (p MD5) Name() string {
	return "md5"
}

func (p MD5) Alias() []string {
	return []string{"md5-sum", "md5-hash"}
}

func (p MD5) Transform(data []byte, opts ...Flag) (string, error) {
	hasher := md5.New()
	hasher.Write(data)

	return hex.EncodeToString(hasher.Sum(nil)), nil
}

func (p MD5) Flags() []Flag {
	return nil
}

func (p MD5) Title() string {
	title := "MD5 Hash"
	return fmt.Sprintf("%s (%s)", title, p.Name())
}

func (p MD5) Description() string {
	return "Generate an MD5 hash of your input"
}

func (p MD5) FilterValue() string {
	return p.Title()
}
