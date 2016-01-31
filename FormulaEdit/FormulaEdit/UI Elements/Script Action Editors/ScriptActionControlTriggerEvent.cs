using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlTriggerEvent : UserControl
    {
        internal ScriptActionControlTriggerEvent(MudData.FormulaActionTriggerEvent action)
        {
            InitializeComponent();

            TargetComboBox.Text = action.target;
            EventComboBox.Text = action.@event;

            foreach (var kvp in action.@params)
            {
                ParamDataGridView.Rows.Add(new object[] { kvp.Key, kvp.Value });
            }
        }
    }
}
