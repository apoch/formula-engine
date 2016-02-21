using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlAddToList : UserControl
    {
        internal ScriptActionControlAddToList(MudData.FormulaActionAddToList action)
        {
            InitializeComponent();

            TargetComboBox.Text = action.target;
            ListComboBox.Text = action.list;
            HostComboBox.Text = action.@object;
        }

        internal MudData.FormulaActionAddToList GenerateMudDataAction()
        {
            var ret = new MudData.FormulaActionAddToList();
            ret.action = "AddToList";
            ret.target = TargetComboBox.Text;
            ret.list = ListComboBox.Text;
            ret.@object = HostComboBox.Text;

            return ret;
        }
    }
}
