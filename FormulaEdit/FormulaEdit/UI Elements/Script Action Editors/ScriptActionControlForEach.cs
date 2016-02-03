using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlForEach : UserControl
    {
        internal ScriptActionControlForEach(MudData.FormulaActionForEach action)
        {
            InitializeComponent();

            ListComboBox.Text = action.list;

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
            ret.actions = ScriptActionEditControl.PopulateMudData(ActionsFlowPanel.Controls);

            return ret;
        }

        private void AddActionButton_Click(object sender, System.EventArgs e)
        {
            // TODO - implement addition of actions to foreach loops
        }
    }
}
