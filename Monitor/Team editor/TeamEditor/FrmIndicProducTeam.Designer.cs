namespace TeamEditor
{
    partial class FrmIndicProducTeam
    {
        /// <summary>
        /// Required designer variable
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }

            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmIndicProducTeam));
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.grdPreview = new System.Windows.Forms.DataGridView();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cboCalendar = new System.Windows.Forms.ComboBox();
            this.cmdQuery = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.cboTeam = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.cboAnnee = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cboModel = new System.Windows.Forms.ComboBox();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdPreview)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.grdPreview);
            this.groupBox2.Location = new System.Drawing.Point(12, 163);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(531, 387);
            this.groupBox2.TabIndex = 13;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Pr�visualisation des r�sultats";
            // 
            // grdPreview
            // 
            this.grdPreview.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdPreview.Location = new System.Drawing.Point(6, 19);
            this.grdPreview.Name = "grdPreview";
            this.grdPreview.Size = new System.Drawing.Size(519, 362);
            this.grdPreview.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.cboCalendar);
            this.groupBox1.Controls.Add(this.cmdQuery);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.cboTeam);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.cboAnnee);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.cboModel);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(531, 145);
            this.groupBox1.TabIndex = 12;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "S�lection";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(23, 114);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 13);
            this.label1.TabIndex = 14;
            this.label1.Text = "Calendrier :";
            // 
            // cboCalendar
            // 
            this.cboCalendar.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboCalendar.FormattingEnabled = true;
            this.cboCalendar.Items.AddRange(new object[] {
            "Calendrier Calcul�",
            "Calendrier Manuel"});
            this.cboCalendar.Location = new System.Drawing.Point(125, 111);
            this.cboCalendar.Name = "cboCalendar";
            this.cboCalendar.Size = new System.Drawing.Size(161, 21);
            this.cboCalendar.TabIndex = 13;
            // 
            // cmdQuery
            // 
            this.cmdQuery.Location = new System.Drawing.Point(333, 109);
            this.cmdQuery.Name = "cmdQuery";
            this.cmdQuery.Size = new System.Drawing.Size(75, 23);
            this.cmdQuery.TabIndex = 12;
            this.cmdQuery.Text = "G�n�ration";
            this.cmdQuery.UseVisualStyleBackColor = true;
            this.cmdQuery.Click += new System.EventHandler(this.cmdQuery_Click_1);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(23, 86);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(46, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Equipe :";
            // 
            // cboTeam
            // 
            this.cboTeam.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboTeam.FormattingEnabled = true;
            this.cboTeam.Location = new System.Drawing.Point(125, 83);
            this.cboTeam.Name = "cboTeam";
            this.cboTeam.Size = new System.Drawing.Size(283, 21);
            this.cboTeam.TabIndex = 10;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(23, 59);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Ann�e :";
            // 
            // cboAnnee
            // 
            this.cboAnnee.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboAnnee.FormattingEnabled = true;
            this.cboAnnee.Location = new System.Drawing.Point(125, 56);
            this.cboAnnee.Name = "cboAnnee";
            this.cboAnnee.Size = new System.Drawing.Size(107, 21);
            this.cboAnnee.TabIndex = 8;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(23, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Model :";
            // 
            // cboModel
            // 
            this.cboModel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboModel.FormattingEnabled = true;
            this.cboModel.Location = new System.Drawing.Point(125, 29);
            this.cboModel.Name = "cboModel";
            this.cboModel.Size = new System.Drawing.Size(283, 21);
            this.cboModel.TabIndex = 6;
            // 
            // FrmIndicProducTeam
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(551, 586);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FrmIndicProducTeam";
            this.Text = "FrmProducTeam";
            this.Load += new System.EventHandler(this.FrmChargeEquipe_Load);
            this.groupBox2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.grdPreview)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.DataGridView grdPreview;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button cmdQuery;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cboTeam;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cboAnnee;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cboModel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cboCalendar;
    }
}