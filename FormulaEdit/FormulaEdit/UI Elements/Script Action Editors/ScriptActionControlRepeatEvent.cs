using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlRepeatEvent : UserControl
    {
        internal ScriptActionControlRepeatEvent(MudData.FormulaActionRepeatEvent action)
        {
            InitializeComponent();

            EventComboBox.Text = action.@event;
            RepeatCountTextBox.Text = action.count;

            foreach (var kvp in action.@params)
            {
                ParamDataGridView.Rows.Add(new object[] { kvp.Key, kvp.Value });
            }
        }

        internal MudData.FormulaActionRepeatEvent GenerateMudDataAction()
        {
            var ret = new MudData.FormulaActionRepeatEvent();
            ret.action = "RepeatEvent";
            ret.@event = EventComboBox.Text;
            ret.count = RepeatCountTextBox.Text;

            foreach (DataGridViewRow row in ParamDataGridView.Rows)
            {
                if (row.Cells.Count != 2)
                    continue;

                string key = row.Cells[0].Value.ToString();
                string value = row.Cells[1].Value.ToString();

                ret.@params[key] = value;
            }

            return ret;
        }
    }
}
