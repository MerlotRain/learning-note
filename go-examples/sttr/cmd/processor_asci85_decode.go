package cmd

import (
	"fmt"
	"os"

	"github.com/merlotrain/rttr/processors"
	"github.com/merlotrain/rttr/utils"
	"github.com/spf13/cobra"
)

func init() {
	rootCmd.AddCommand(ascii85DecodeCmd)
}

var ascii85DecodeCmd = &cobra.Command{
	Use:     "ascii85-decode [string]",
	Short:   "Decode your text to Ascii85 ( Base85 ) text",
	Aliases: []string{"ascii85-decoding", "base85-decode", "b85-decode"},
	Args:    cobra.MaximumNArgs(1),
	RunE: func(cmd *cobra.Command, args []string) error {
		var err error
		var in []byte
		var out string

		if len(args) == 0 {
			in = []byte(utils.ReadMultilineInput())
		} else {
			if fi, err := os.Stat(args[0]); err == nil && !fi.IsDir() {
				d, err := os.ReadFile(args[0])
				if err != nil {
					return err
				}
				in = d
			} else {
				in = []byte(args[0])
			}
		}

		flags := make([]processors.Flag, 0)
		p := processors.ASCII85Decoding{}

		out, err = p.Transform(in, flags...)
		if err != nil {
			return err
		}

		_, err = fmt.Fprint(os.Stdout, out)
		return err
	},
}
