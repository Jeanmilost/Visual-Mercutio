/********************************************************************************************************
 *                                             Classe WordInstance                                      *
 ********************************************************************************************************
 * Auteur   : Jean-Milost Reymond                                                                       *
 * Date     : Le 1er avril 2007                                                                         *
 * Version  : 1.0                                                                                       *
 ********************************************************************************************************
 * Cette classe permet de g�rer un fichier de configuration pour le programme. Elle cr�e le fichier,    *
 * et permet la lecture ou l'inscription des paires cl�s/valeurs dans celui-ci.                         *
 ********************************************************************************************************/

using System;
using System.IO;
using System.Windows.Forms;
using System.Diagnostics;

namespace ReportsTool.FilesManager
{
    public class ConfigFile
    {
        #region D�finition du Singleton de la classe

        /// <summary>
        /// La seule et unique instance de la classe ConfigFile.
        /// </summary>
        protected static readonly ConfigFile p_Instance = new ConfigFile();

        #endregion

        #region Variables globales

        private string s_Filename       = "Config.ini";
        private string s_ReservedChar   = "#";
        private string s_OpenKey        = "[";
        private string s_CloseKey       = "]";

        #endregion

        #region Constructeur(s) / Destructeur

        /// <summary>
        /// Le constructeur est priv�, ce qui interdit la construction d'une autre instance pour cette classe.
        /// </summary>
        private ConfigFile()
        {
        }

        #endregion

        #region Propri�t�s de la classe

        /// <summary>
        /// Retourne un pointeur sur l'instance unique de la classe.
        /// </summary>
        public static ConfigFile Instance
        {
            get
            {
                return p_Instance;
            }
        }

        #endregion

        #region Fonctions publiques

        /// <summary>
        /// Cette fonction permet de d�terminer si le fichier de configuration a d�j� �t� cr�e.
        /// </summary>
        /// <returns>True si le fichier est cr�e, sinon False.</returns>
        public bool Exists()
        {
            return File.Exists(s_Filename);
        }

        /// <summary>
        /// Cette fonction permet de cr�er un fichier de configuration, vide.
        /// </summary>
        public void Create()
        {
            try
            {
                File.Create(s_Filename);
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function Create failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_CANNOT_CREATE_INI_FILE") + ex.Message,
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction permet de lire une valeur dans le fichier.
        /// </summary>
        /// <param name="Key">La cl� correspondant � la valeur � lire.</param>
        /// <returns>La valeur de la cl�.</returns>
        public string Read(string Key)
        {
            try
            {
                FileStream oReadStream = new FileStream(s_Filename,
                                                        FileMode.OpenOrCreate,
                                                        FileAccess.Read,
                                                        FileShare.None);

                StreamReader oFileReader = new StreamReader(oReadStream, System.Text.Encoding.Default);

                while (oFileReader.Peek() != -1)
                {
                    string theLine = oFileReader.ReadLine();

                    if (theLine.Contains(FormatKey(Key)))
                    {
                        string[] theValues = theLine.Split('=');

                        oFileReader.Close();
                        oReadStream.Close();

                        return theValues[theValues.Length - 1];
                    }
                }

                oFileReader.Close();
                oReadStream.Close();
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function Read failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_CANNOT_READ_KEY") + ex.Message,
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }

            return "";
        }

        /// <summary>
        /// Cette fonction permet d'�crire une paire cl�/valeur dans le fichier de configuration.
        /// Si la cl� existe d�j� dans le fichier, celle-ci est simplement mise � jour.
        /// </summary>
        /// <param name="Key">La cl�, sans les caract�res [ et ].</param>
        /// <param name="Value">La valeur � attribuer � la cl�.</param>
        public void Write(string Key, string Value)
        {
            try
            {
                if (Key.Contains(s_ReservedChar) || Key.Contains(s_OpenKey) || Key.Contains(s_CloseKey))
                {
                    throw new Exception(InsertString("IDS_WRONG_KEY_FORMAT", FormatKey(Key)));
                }

                if (Value.Contains(s_ReservedChar) || Value.Contains(s_OpenKey) || Value.Contains(s_CloseKey))
                {
                    throw new Exception(InsertString("IDS_WRONG_VALUE_FORMAT", Value));
                }

                if (KeyExist(Key) == false)
                {
                    WriteNewLine(Key, Value);
                }
                else
                {
                    OverWrite(Key, Value);
                }
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function Write failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_CANNOT_WRITE_KEY") + ex.Message,
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        #endregion

        #region Fonctions priv�es

        /// <summary>
        /// Cette fonction permet de d�terminer si une cl� existe dans le fichier de configuration.
        /// </summary>
        /// <param name="Key">La cl�, sans les caract�res [ et ].</param>
        /// <returns>true si la cl� existe, sinon false.</returns>
        private bool KeyExist(string Key)
        {
            try
            {
                FileStream oReadStream = new FileStream(s_Filename,
                                                        FileMode.OpenOrCreate,
                                                        FileAccess.Read,
                                                        FileShare.None);

                StreamReader oFileReader = new StreamReader(oReadStream, System.Text.Encoding.Default);

                while (oFileReader.Peek() != -1)
                {
                    string theLine = oFileReader.ReadLine();

                    if (theLine.Contains(FormatKey(Key)))
                    {
                        oFileReader.Close();
                        oReadStream.Close();

                        return true;
                    }
                }

                oFileReader.Close();
                oReadStream.Close();
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function KeyExist failed. Cause : " + ex.Message);
                throw new Exception(ex.Message);
            }

            return false;
        }

        /// <summary>
        /// Cette fonction permet d'�crire une nouvelle paire cl�/valeur dans le fichier.
        /// </summary>
        /// <param name="Key">La cl�, sans les caract�res [ et ].</param>
        /// <param name="Value">La valeur de la cl�.</param>
        private void WriteNewLine(string Key, string Value)
        {
            try
            {
                FileStream oWriteStream = new FileStream(s_Filename,
                                                         FileMode.Append,
                                                         FileAccess.Write,
                                                         FileShare.None);

                StreamWriter oFileWriter = new StreamWriter(oWriteStream, System.Text.Encoding.Default);

                oFileWriter.WriteLine(FormatKey(Key) + "=" + Value);

                oFileWriter.Close();
                oWriteStream.Close();
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function WriteLine failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_CANNOT_WRITE_KEY") + ex.Message,
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction permet de mettre � jour une valeur pour une cl� existante dans le fichier.
        /// </summary>
        /// <param name="Key">La cl�, sans les caract�res [ et ].</param>
        /// <param name="Value">La valeur de la cl� � mettre � jour.</param>
        private void OverWrite(string Key, string Value)
        {
            try
            {
                FileStream oReadStream = new FileStream(s_Filename,
                                                        FileMode.OpenOrCreate,
                                                        FileAccess.Read,
                                                        FileShare.None);

                StreamReader oFileReader = new StreamReader(oReadStream, System.Text.Encoding.Default);

                string s_FileContent = "";

                while (oFileReader.Peek() != -1)
                {
                    s_FileContent += oFileReader.ReadLine() + s_ReservedChar;
                }

                oFileReader.Close();
                oReadStream.Close();

                File.Delete(s_Filename);

                string[] s_File = s_FileContent.Split(s_ReservedChar.ToCharArray());

                FileStream oWriteStream = new FileStream(s_Filename,
                                                         FileMode.OpenOrCreate,
                                                         FileAccess.Write,
                                                         FileShare.None);

                StreamWriter oFileWriter = new StreamWriter(oWriteStream, System.Text.Encoding.Default);

                for (int i = 0; i < s_File.Length - 1; i++)
                {
                    if (s_File[i].Contains(FormatKey(Key)))
                    {
                        oFileWriter.WriteLine(FormatKey(Key) + "=" + Value);
                    }
                    else
                    {
                        oFileWriter.WriteLine(s_File[i]);
                    }
                }

                oFileWriter.Close();
                oWriteStream.Close();
            }
            catch (Exception ex)
            {
                Trace.WriteLine("Class ConfigFile -> Function OverWrite failed. Cause : " + ex.Message);

                MessageBox.Show(Culture.Culture.Instance.GetStr("IDS_CANNOT_WRITE_KEY") + ex.Message,
                                Culture.Culture.Instance.GetStr("IDS_APPTITLE"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Cette fonction retourne une cl� format�e.
        /// </summary>
        /// <param name="Key">La cl� � formater.</param>
        /// <returns>La cl� format�e.</returns>
        private string FormatKey(string Key)
        {
            return s_OpenKey + Key + s_CloseKey;
        }

        /// <summary>
        /// Cette fonction permet de rempla�er la valeur %s par un mot ou une phrase dans une cha�ne de caract�res.
        /// </summary>
        /// <param name="ID">L'ID de la cha�ne � charger.</param>
        /// <param name="Value">La valeur de remplacement pour %s.</param>
        /// <returns></returns>
        private string InsertString(string ID, string Value)
        {
            return Culture.Culture.Instance.GetStr(ID).Replace("%s", Value);
        }

        #endregion
    }
}
