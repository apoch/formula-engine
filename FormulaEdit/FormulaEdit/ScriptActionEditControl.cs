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

        private Dictionary<string, string> PopulateActionDictionary()
        {
            var ret = new Dictionary<string, string>();

            ret["action"] = ActionComboBox.Text;
            foreach (DataGridViewRow row in ActionDataGrid.Rows)
            {
                var cells = row.Cells;

                if (cells.Count != 2)
                    continue;

                if (cells[0].Value == null)
                    continue;

                if (cells[1].Value == null)
                    continue;

                ret[cells[0].Value.ToString()] = cells[1].Value.ToString();
            }

            return ret;
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

        public static List<Dictionary<string, string>> PopulateMudData(ContainerControl.ControlCollection controls)
        {
            var ret = new List<Dictionary<string, string>>();

            foreach (ScriptActionEditControl ctl in controls)
            {
                ret.Add(ctl.PopulateActionDictionary());
            }

            return ret;
        }
    }
}
