using System;
using System.Windows.Forms;
using ProcesssoftDLL;

namespace TeamEditor
{
    public partial class FrmIndicNbrCasTraite : Form
    {
        private Indicator m_Indic;
        private int       m_ModelID;
        private int       m_Year;
        private int       m_ProcessID;

        public FrmIndicNbrCasTraite()
        {
            InitializeComponent();

            m_Indic = new Indicator();
        }

        private void FrmIndicNbrCasTraite_Load(object sender, EventArgs e)
        {
            PModel pModel = new PModel();

            // load model id combo
            cboModel.DisplayMember = "model";
            cboModel.ValueMember   = "modelid";
            cboModel.DataSource    = pModel.getListForComboBox().Tables[0];

            // load year combo
            loadComboYear();

            // update after the combo selection
            updateComboSelection();

            // load ComboProcess
            LoadComboProcess();
        }

        private void loadComboYear()
        {
            for (int i = 1990; i <= DateTime.Now.Year; ++i)
                cboAnnee.Items.Add(Convert.ToString(i));

            cboAnnee.SelectedIndex = cboAnnee.Items.Count - 1;
        }

        private void LoadComboProcess()
        {
            cboProc.DisplayMember = "processname";
            cboProc.ValueMember   = "processid";
            cboProc.DataSource    = m_Indic.GetProcessList(m_ModelID).Tables[0];
        }

        private void updateComboSelection()
        {
            m_ModelID = Convert.ToInt32(cboModel.SelectedValue);
        }

        private void cmdQuery_Click(object sender, EventArgs e)
        {
            m_Year      = Convert.ToInt32(cboAnnee.SelectedItem);
            m_ProcessID = Convert.ToInt32(cboProc.SelectedValue);

            grdPreview.DataSource = m_Indic.QueryIndicatorNbrCasTraite(m_ProcessID, m_Year);
            grdPreview.DataMember = "Table";

            // fill label table
            Indicator indic = new Indicator();
            indic.AddLabel(m_Year, cboProc.Text);

            MessageBox.Show("G�n�ration de l'indicateur \"" + this.Text + "\" termin�e");
        }
    }
}
