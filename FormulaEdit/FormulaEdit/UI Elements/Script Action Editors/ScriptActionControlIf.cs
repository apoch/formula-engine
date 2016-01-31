using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlIf : UserControl
    {
        internal ScriptActionControlIf(MudData.FormulaActionIf action)
        {
            InitializeComponent();

            ConditionTextBox.Text = action.condition;

            ScriptActionEditControl.PopulatePanel(action.actions, ActionsFlowPanel);
            ScriptActionEditControl.PopulatePanel(action.@else, ElseActionsFlowPanel);
        }
    }
}
