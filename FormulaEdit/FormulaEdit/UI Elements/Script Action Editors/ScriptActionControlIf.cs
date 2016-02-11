using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlIf : UserControl
    {
        private string EditingArchetypeName = "";

        internal ScriptActionControlIf(MudData.FormulaActionIf action, string archetypeName)
        {
            InitializeComponent();

            EditingArchetypeName = archetypeName;

            ConditionTextBox.Text = action.condition;

            ScriptActionEditControl.PopulatePanel(action.actions, ActionsFlowPanel, EditingArchetypeName);
            ScriptActionEditControl.PopulatePanel(action.@else, ElseActionsFlowPanel, EditingArchetypeName);
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
            ActionsFlowPanel.Controls.Add(new ScriptActionEditControl(new MudData.FormulaActionSetGoalState(), EditingArchetypeName));
            Utilities.ResizeControls(ActionsFlowPanel);
        }

        private void AddElseActionButton_Click(object sender, System.EventArgs e)
        {
            ElseActionsFlowPanel.Controls.Add(new ScriptActionEditControl(new MudData.FormulaActionSetGoalState(), EditingArchetypeName));
            Utilities.ResizeControls(ElseActionsFlowPanel);
        }
    }
}
