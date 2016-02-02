using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlCreateListMember : UserControl
    {
        internal ScriptActionControlCreateListMember(MudData.FormulaActionCreateListMember action)
        {
            InitializeComponent();

            ListComboBox.Text = action.list;
            ArchetypeComboBox.Text = action.archetype;

            foreach (var kvp in action.@params)
            {
                ParamDataGridView.Rows.Add(new object[] { kvp.Key, kvp.Value });
            }
        }

        internal MudData.FormulaActionCreateListMember GenerateMudDataAction()
        {
            var ret = new MudData.FormulaActionCreateListMember();
            ret.action = "CreateListMember";
            ret.list = ListComboBox.Text;
            ret.archetype = ArchetypeComboBox.Text;

            foreach (DataGridViewRow row in ParamDataGridView.Rows)
            {
                if (row.Cells.Count != 2)
                    continue;

                string key = row.Cells[0].Value.ToString();
                string value = row.Cells[1].Value.ToString();

                ret.@params[key] = value;
            }

            return ret;
        }
    }
}
