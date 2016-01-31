using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlAddSelfToList : UserControl
    {
        internal ScriptActionControlAddSelfToList(MudData.FormulaActionAddSelfToList action)
        {
            InitializeComponent();

            TargetComboBox.Text = action.target;
            ListComboBox.Text = action.list;
        }
    }
}
