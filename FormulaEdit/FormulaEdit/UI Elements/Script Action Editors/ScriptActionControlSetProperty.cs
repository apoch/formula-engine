using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlSetProperty : UserControl
    {
        internal ScriptActionControlSetProperty(MudData.FormulaActionSetProperty action)
        {
            InitializeComponent();

            PropertyComboBox.Text = action.property;
            FormulaTextBox.Text = action.value;
        }
    }
}
