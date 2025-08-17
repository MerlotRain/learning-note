package cmd

import (
	"fmt"
	"os"

	"github.com/merlotrain/rttr/ui"
	"github.com/spf13/cobra"
)

var rootCmd = &cobra.Command{
	Use:   "rttr",
	Short: "sttr is a fast and flexible string/text converter",
	Long: `sttr is a command line tool that allows you to quickly apply various 
transformation operations on the input text.

Complete documentation is available at https://github.com/merlotrain/rttr`,
	RunE: func(cmd *cobra.Command, args []string) error {
		if len(args) == 0 {
			x := ui.New("")
			x.Render()
		}
		return nil
	},
}

func init() {
}

func Execute() {
	if err := rootCmd.Execute(); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}
