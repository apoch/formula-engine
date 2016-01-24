using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FormulaEdit
{
    public partial class ScriptActionEditControl : UserControl
    {
        public ScriptActionEditControl(Dictionary<string, string> kvp)
        {
            InitializeComponent();

            foreach (var pair in kvp)
            {
                if (pair.Key == "action")
                {
                    foreach (var item in ActionComboBox.Items)
                    {
                        if (item.ToString().Equals(pair.Value))
                        {
                            ActionComboBox.SelectedItem = item;
                            break;
                        }
                    }
                }
                else
                {
                    ActionDataGrid.Rows.Add(new object[] { pair.Key, pair.Value });
                }
            }
        }


        public static void PopulatePanel(List<Dictionary<string, string>> actions, Panel panel)
        {
            foreach (var action in actions)
            {
                var editor = new ScriptActionEditControl(action);
                panel.Controls.Add(editor);

                editor.Width = panel.ClientSize.Width - (editor.Left * 2);
                editor.Height = (editor.ActionDataGrid.RowCount + 2) * 25;            // TODO - evil magic number

                editor.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            }
        }
    }
}
