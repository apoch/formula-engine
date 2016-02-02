using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlSetGoalState : UserControl
    {
        internal ScriptActionControlSetGoalState(MudData.FormulaActionSetGoalState action)
        {
            InitializeComponent();

            BindingComboBox.Text = action.binding;
            PropertyComboBox.Text = action.property;
            ValueTextBox.Text = action.value;
        }

        internal MudData.FormulaActionSetGoalState GenerateMudDataAction()
        {
            var ret = new MudData.FormulaActionSetGoalState();
            ret.action = "SetGoalState";
            ret.binding = BindingComboBox.Text;
            ret.property = PropertyComboBox.Text;
            ret.value = ValueTextBox.Text;

            return ret;
        }
    }
}
