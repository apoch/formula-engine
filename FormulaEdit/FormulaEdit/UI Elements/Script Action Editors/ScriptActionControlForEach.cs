using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlForEach : UserControl
    {
        internal ScriptActionControlForEach(MudData.FormulaActionForEach action)
        {
            InitializeComponent();

            ListComboBox.Text = action.list;
            ScriptableComboBox.Text = action.scriptable;

            ActionsFlowPanel.Resize += (ctl, args) => {
                Utilities.ResizeControls(ActionsFlowPanel);
            };

            ScriptActionEditControl.PopulatePanel(action.actions, ActionsFlowPanel);
        }

        internal MudData.FormulaActionForEach GenerateMudDataAction()
        {
            var ret = new MudData.FormulaActionForEach();
            ret.action = "foreach";
            ret.list = ListComboBox.Text;
            ret.scriptable = ScriptableComboBox.Text;
            ret.actions = ScriptActionEditControl.PopulateMudData(ActionsFlowPanel.Controls);

            return ret;
        }

        private void AddActionButton_Click(object sender, System.EventArgs e)
        {
            ActionsFlowPanel.Controls.Add(new ScriptActionEditControl(new MudData.FormulaActionSetGoalState()));
            Utilities.ResizeControls(ActionsFlowPanel);
        }
    }
}
