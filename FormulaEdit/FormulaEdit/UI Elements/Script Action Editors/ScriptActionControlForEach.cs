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
    }
}
