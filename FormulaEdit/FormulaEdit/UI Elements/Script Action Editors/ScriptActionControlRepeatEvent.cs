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
    }
}
