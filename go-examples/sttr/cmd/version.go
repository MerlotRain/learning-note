package cmd

import (
	"fmt"

	"github.com/spf13/cobra"
)

var Version = "1.0.0"

func init() {

}

var versionComd = &cobra.Command{
	Use:   "version",
	Short: "Print the version of rttr",
	Long:  "All software has a version (semantic at best). This is sttr's'",
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println(Version)
	},
}
