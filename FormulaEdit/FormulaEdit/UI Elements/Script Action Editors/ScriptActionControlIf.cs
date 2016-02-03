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

        internal MudData.FormulaActionIf GenerateMudDataAction()
        {
            var ret = new MudData.FormulaActionIf();
            ret.action = "if";
            ret.condition = ConditionTextBox.Text;
            ret.actions = ScriptActionEditControl.PopulateMudData(ActionsFlowPanel.Controls);
            ret.@else = ScriptActionEditControl.PopulateMudData(ElseActionsFlowPanel.Controls);

            return ret;
        }

        private void AddActionButton_Click(object sender, System.EventArgs e)
        {
            // TODO - implement addition of actions to if statements
        }

        private void AddElseActionButton_Click(object sender, System.EventArgs e)
        {
            // TODO - implement addition of actions to else blocks
        }
    }
}
