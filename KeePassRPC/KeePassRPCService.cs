﻿/*
  KeePassRPC - Uses JSON-RPC to provide RPC facilities to KeePass.
  Example usage includes the KeeFox firefox extension.
  
  Copyright 2010 Chris Tomlinson <keefox@christomlinson.name>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

using System;
using System.Collections.Generic;
using System.Text;
using Jayrock.JsonRpc;
using KeePassRPC.DataExchangeModel;
using System.Threading;
using System.Windows.Forms;
using KeePass.Forms;
using KeePassLib;
using System.Collections;
using System.Drawing;
using KeePass.Resources;
using KeePassLib.Serialization;
using System.IO;
using KeePassLib.Security;
using KeePass.Plugins;

namespace KeePassRPC
{
    /// <summary>
    /// Provides an externally accessible API for common KeePass operations
    /// </summary>
    public class KeePassRPCService : JsonRpcService
    {
        #region Class variables, constructor and destructor

        Version PluginVersion;
        IPluginHost host;
        // no way to make use of this yet: bool permitUnencryptedURLs = false;

        // naive way to block synchronous operations until user responds to a database login dialog - likely to require more sophistication when more than one RPC client connects at the same time.
        internal static EventWaitHandle ensureDBisOpenEWH = new AutoResetEvent(false);

        private string[] _standardIconsBase64;

        public KeePassRPCService(IPluginHost host, string[] standardIconsBase64, Version pluginVersion)
        {
            PluginVersion = pluginVersion;
            this.host = host;
            _standardIconsBase64 = standardIconsBase64;
        }

        // why?
        public void destroy()
        {
            // why?
            lock (this)
            {
                // why?
                System.Threading.Monitor.Pulse(this);
            }
        }
        #endregion

        #region Client authentication

        /// <summary>
        /// Authenticates an RPC client by verifying it is the correct version, is in possesion of an identifying string encrypted by the private key companian of the public key embedded in this application and that hash of its unique ID data matches that stored in the KeePass config file. Unrecognised clients will be presented to the user for one-time validation.
        /// </summary>
        /// <param name="versionParts">The version of the client (must be identical to this RPC plugin version for authentication to succeed)</param>
        /// <param name="b64Id">Base64 encoded unique id.</param>
        /// <param name="b64PrivId">Base64 encoded client type identifer (encrypted by a private key)</param>
        /// <returns>0 if authentication was approved; other positive integers to indicate various error conditions</returns>
        [JsonRpcMethod]
        public int Authenticate(int[] versionParts, string b64Id, string b64PrivId)
        {
            return 0; // authenticated and versions match!!!!!!!!!!!!!!!!!!!!!!!!!
            //TODO: !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            //do version negotiation first so C and S know they'll be using correct key pairs (in case some are changed in future).

            //A(k) = encrypted KeeFoxID string where A is private (only developer knows)
            //A(k) is decrypted by B() where server knows (public) B

            //C sends A(k) to S
            //C sends X(A(k)) to S where X is based on private encryption key (generated at random on first connect and then stored in KeeFox profile)
            //S calculates string ID using B(A(k))
            //S calculates hash1 = H(X(A(k)) + string ID)
            //S stores hash1 in KeePass config file

            //Main limitations are that private keys will be stored on the client without protection. File system level protection may help, as might use of Firefox master password? Other clients may face similar challenges.
            //Modification of hash1 could provide a means for attacker to use a spoofed client machine to connect but string ID is recalculated each time using public key held in program code so cos the hash is based on that, attacker can't control the actual hash value that the server is expecting - therefore modification of the hash key is at worst a DOS.

            bool versionMatch = false;
            //TODO: sanitation
            Version versionClient = new Version(versionParts[0], versionParts[1], versionParts[2]);

            if (PluginVersion.CompareTo(versionClient) == 0)
                versionMatch = true;

            if (versionMatch == false)
                return 2; // version mismatch

            //S calculates string ID using B(A(k))
            string clientID = "keefox";

            //S calculates hash1 = H(X(A(k)) + string ID)
            string hash = "hash of: " + b64PrivId + clientID;

            //First authentication, user must confirm string ID is expected.
            MessageBox.Show("KeePassRPC detected an attempt to connect to KeePass. Please verify it was expected, blah, blah, blah.");
            // if so, S stores hash in KeePass config file, indexed upon the clientID

            //TODO: audit logging options? needs to be a KeePass supported feature really or maybe a seperate plugin?
            return 1; // General authentication system error
        }

        #endregion

        #region KeePass GUI routines

        /// <summary>
        /// Halts thread until a DB is open in the KeePass application
        /// </summary>
        /// <remarks>This simple thread sync may not work if more than one RPC client gets involved.</remarks>
        private bool ensureDBisOpen()
        {

            if (!host.Database.IsOpen)
            {
                ensureDBisOpenEWH.Reset(); // ensures we will wait even if DB has been opened previously.
                // maybe tiny opportunity for deadlock if user opens DB exactly between DB.IsOpen and this statement?
                // TODO: consider moving above statement to top of method - shouldn't do any harm and could rule out rare deadlock?
                host.MainWindow.BeginInvoke(new MethodInvoker(promptUserToOpenDB));
                ensureDBisOpenEWH.WaitOne(15000, false); // wait until DB has been opened

                if (!host.Database.IsOpen)
                    return false;
            }
            return true;
        }

        void promptUserToOpenDB()
        {
            /*
             * I think this form would be used to choose a different file to open but haven't tried it.
             * At least for now, the MRU file is the only option we'll tightly integrate with KeeICE
             * If user is advanced enough to know about multiple databases, etc. they can quit this
             * function and open their database via usual KeePass methods
             * 
            KeePass.Forms.IOConnectionForm form1 = new IOConnectionForm();
            form1.InitEx();
            
            */

            KeePass.Program.MainForm.OpenDatabase(KeePass.Program.Config.Application.LastUsedFile, null, false);

            if (!host.Database.IsOpen)
                ensureDBisOpenEWH.Set(); // signal that any waiting RPC client thread can go ahead
        }

        void saveDB()
        {
            if (host.CustomConfig.GetBool("KeePassRPC.KeeFox.autoCommit", true))
            {
                if (host.MainWindow.UIFileSave(true))
                    host.MainWindow.UpdateUI(false, null, true, null, true, null, false);
            }
            else
            {
                host.MainWindow.UpdateUI(false, null, true, null, true, null, true);
            }
        }

        void openGroupEditorWindow(PwGroup pg)
        {
            GroupForm gf = new GroupForm();
            gf.InitEx(pg, host.MainWindow.ClientIcons, host.Database);

            gf.BringToFront();
            gf.ShowInTaskbar = true;

            host.MainWindow.Focus();
            gf.TopMost = true;
            gf.Focus();
            gf.Activate();
            if (gf.ShowDialog() == DialogResult.OK)
                saveDB();
        }

        private delegate void dlgOpenGroupEditorWindow(PwGroup pg);

        /// <summary>
        /// Launches the group editor.
        /// </summary>
        /// <param name="uuid">The UUID of the group to edit.</param>
        [JsonRpcMethod]
        public void LaunchGroupEditor(string uuid)
        {
            // Make sure there is an active database
            if (!ensureDBisOpen()) return;

            if (uuid != null && uuid.Length > 0)
            {
                PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(uuid));

                PwGroup matchedGroup = GetRootPwGroup().FindGroup(pwuuid, true);

                if (matchedGroup == null)
                    throw new Exception("Could not find requested entry.");

                host.MainWindow.Invoke(new dlgOpenGroupEditorWindow(openGroupEditorWindow), matchedGroup);
            }

        }

        void OpenLoginEditorWindow(PwEntry pe)
        {
            //TODO: focus existing editor window for this login if there is one. Maybe use host.MainWindow.OwnedForms or keep our own list of open forms in this plugin (and destroy them when plugin is destroyed) + same for Group editor
            PwEntryForm ef = new PwEntryForm();
            ef.InitEx(pe, PwEditMode.EditExistingEntry, host.Database, host.MainWindow.ClientIcons, false, false);

            ef.BringToFront();
            ef.ShowInTaskbar = true;

            host.MainWindow.Focus();
            ef.TopMost = true;
            ef.Focus();
            ef.Activate();

            if (ef.ShowDialog() == DialogResult.OK)
                saveDB();
        }

        private delegate void dlgOpenLoginEditorWindow(PwEntry pg);

        /// <summary>
        /// Launches the login editor.
        /// </summary>
        /// <param name="uuid">The UUID of the entry to edit.</param>
        [JsonRpcMethod]
        public void LaunchLoginEditor(string uuid)
        {
            // Make sure there is an active database
            if (!ensureDBisOpen()) return;

            if (uuid != null && uuid.Length > 0)
            {
                PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(uuid));

                PwEntry matchedLogin = GetRootPwGroup().FindEntry(pwuuid, true);

                if (matchedLogin == null)
                    throw new Exception("Could not find requested entry.");

                host.MainWindow.Invoke(new dlgOpenLoginEditorWindow(OpenLoginEditorWindow), matchedLogin);
            }

        }

        #endregion
        
        #region Utility functions to convert between KeePassRPC object schema and KeePass schema

        private Entry GetEntryFromPwEntry(PwEntry pwe, bool isExactMatch)
        {
            ArrayList formFieldList = new ArrayList();
            ArrayList URLs = new ArrayList();
            URLs.Add(pwe.Strings.ReadSafe("URL"));
            bool usernameFound = false;
            bool passwordFound = false;
            bool alwaysAutoFill = false;
            bool neverAutoFill = false;
            bool alwaysAutoSubmit = false;
            bool neverAutoSubmit = false;
            int priority = 0;

            foreach (System.Collections.Generic.KeyValuePair
                <string, KeePassLib.Security.ProtectedString> pwestring in pwe.Strings)
            {
                string pweKey = pwestring.Key;
                string pweValue = pwestring.Value.ReadString();

                if (pweKey.StartsWith("Form field ") && pweKey.EndsWith(" type") && pweKey.Length > 16)
                {
                    string fieldName = pweKey.Substring(11).Substring(0, pweKey.Length - 11 - 5);
                    string fieldId = "";
                    int fieldPage = 1;

                    if (pwe.Strings.Exists("Form field " + fieldName + " page"))
                    {
                        try
                        {
                            fieldPage = int.Parse(pwe.Strings.ReadSafe("Form field " + fieldName + " page"));
                        }
                        catch (Exception)
                        {
                            fieldPage = 1;
                        }
                    }


                    if (pwe.Strings.Exists("Form field " + fieldName + " id"))
                        fieldId = pwe.Strings.ReadSafe("Form field " + fieldName + " id");

                    if (pweValue == "password")
                    {
                        // If there is a matching custom string for this password, use that but if not
                        // we can just use the standard entry password.
                        if (pwe.Strings.Exists("Form field " + fieldName + " value"))
                            formFieldList.Add(new FormField(fieldName,
                "Password", pwe.Strings.ReadSafe("Form field " + fieldName + " value"), FormFieldType.FFTpassword, fieldId, fieldPage));
                        else
                            formFieldList.Add(new FormField(fieldName,
                "Password", pwe.Strings.ReadSafe("Password"), FormFieldType.FFTpassword, fieldId, fieldPage));
                        passwordFound = true;
                    }
                    else if (pweValue == "username")
                    {
                        formFieldList.Add(new FormField(fieldName,
                "User name", pwe.Strings.ReadSafe("UserName"), FormFieldType.FFTusername, fieldId, fieldPage));
                        usernameFound = true;
                    }
                    else if (pweValue == "text")
                    {
                        formFieldList.Add(new FormField(fieldName,
                fieldName, pwe.Strings.ReadSafe("Form field " + fieldName + " value"), FormFieldType.FFTtext, fieldId, fieldPage));
                    }
                    else if (pweValue == "radio")
                    {
                        formFieldList.Add(new FormField(fieldName,
                fieldName, pwe.Strings.ReadSafe("Form field " + fieldName + " value"), FormFieldType.FFTradio, fieldId, fieldPage));
                    }
                    else if (pweValue == "select")
                    {
                        formFieldList.Add(new FormField(fieldName,
                fieldName, pwe.Strings.ReadSafe("Form field " + fieldName + " value"), FormFieldType.FFTselect, fieldId, fieldPage));
                    }
                    else if (pweValue == "checkbox")
                    {
                        formFieldList.Add(new FormField(fieldName,
                fieldName, pwe.Strings.ReadSafe("Form field " + fieldName + " value"), FormFieldType.FFTcheckbox, fieldId, fieldPage));
                    }
                }
                else if (pweKey == "Alternative URLs")
                {
                    string[] urlsArray = pweValue.Split(new char[' ']);
                    foreach (string altURL in urlsArray)
                        URLs.Add(altURL);

                }

            }

            // If we didn't find an explicit password field, we assume any value
            // in the KeePass "password" box is what we are looking for
            if (!passwordFound)
            {
                formFieldList.Add(new FormField("password",
                    "Password", pwe.Strings.ReadSafe("Password"), FormFieldType.FFTpassword, "password", 1));
            }

            // If we didn't find an explicit username field, we assume any value
            // in the KeePass "username" box is what we are looking for
            if (!usernameFound)
            {
                formFieldList.Add(new FormField("username",
                    "Username", pwe.Strings.ReadSafe("UserName"), FormFieldType.FFTusername, "username", 1));
            }

            string imageData = iconToBase64(pwe.CustomIconUuid, pwe.IconId);

            if (pwe.Strings.Exists("KeeFox Always Auto Fill"))
                alwaysAutoFill = true;
            if (pwe.Strings.Exists("KeeFox Always Auto Submit"))
                alwaysAutoSubmit = true;
            if (pwe.Strings.Exists("KeeFox Never Auto Fill"))
                neverAutoFill = true;
            if (pwe.Strings.Exists("KeeFox Never Auto Submit"))
                neverAutoSubmit = true;

            if (pwe.Strings.Exists("KeeFox Priority"))
            {
                string priorityString = pwe.Strings.ReadSafe("KeeFox Priority");
                if (!string.IsNullOrEmpty(priorityString))
                {
                    try
                    {
                        priority = int.Parse(priorityString);
                    }
                    catch
                    { }

                    if (priority < 0 || priority > 100000)
                        priority = 0;
                }
            }

            FormField[] temp = (FormField[])formFieldList.ToArray(typeof(FormField));
            Entry kpe = new Entry(
                (string[])URLs.ToArray(typeof(string)),
                pwe.Strings.ReadSafe("Form match URL"), pwe.Strings.ReadSafe("Form HTTP realm"),
                pwe.Strings.ReadSafe(PwDefs.TitleField), temp,
                KeePassLib.Utility.MemUtil.ByteArrayToHexString(pwe.Uuid.UuidBytes),
                alwaysAutoFill, neverAutoFill, alwaysAutoSubmit, neverAutoSubmit, priority,
                GetGroupFromPwGroup(pwe.ParentGroup), imageData);
            return kpe;
        }

        private Group GetGroupFromPwGroup(PwGroup pwg)
        {
            string imageData = iconToBase64(pwg.CustomIconUuid, pwg.IconId);

            Group kpg = new Group(pwg.Name, KeePassLib.Utility.MemUtil.ByteArrayToHexString(pwg.Uuid.UuidBytes), imageData, pwg.GetFullPath("/", false));
            return kpg;
        }

        private void setPwEntryFromEntry(PwEntry pwe, Entry login)
        {
            bool firstPasswordFound = false;

            foreach (FormField kpff in login.FormFieldList)
            {
                if (kpff.Type == FormFieldType.FFTpassword && !firstPasswordFound)
                {
                    pwe.Strings.Set("Password", new ProtectedString(host.Database.MemoryProtection.ProtectPassword, kpff.Value));
                    pwe.Strings.Set("Form field " + kpff.Name + " type", new ProtectedString(false, "password"));
                    firstPasswordFound = true;
                }
                else if (kpff.Type == FormFieldType.FFTpassword)
                {
                    pwe.Strings.Set("Form field " + kpff.Name + " value", new ProtectedString(host.Database.MemoryProtection.ProtectPassword, kpff.Value)); // we protect this string if user has asked to protect passwords
                    pwe.Strings.Set("Form field " + kpff.Name + " type", new ProtectedString(false, "password"));
                }
                else if (kpff.Type == FormFieldType.FFTusername)
                {
                    pwe.Strings.Set("UserName", new ProtectedString(host.Database.MemoryProtection.ProtectUserName, kpff.Value));
                    pwe.Strings.Set("Form field " + kpff.Name + " type", new ProtectedString(false, "username"));
                }
                else if (kpff.Type == FormFieldType.FFTtext)
                {
                    pwe.Strings.Set("Form field " + kpff.Name + " value", new ProtectedString(false, kpff.Value));
                    pwe.Strings.Set("Form field " + kpff.Name + " type", new ProtectedString(false, "text"));
                }
                else if (kpff.Type == FormFieldType.FFTcheckbox)
                {
                    pwe.Strings.Set("Form field " + kpff.Name + " value", new ProtectedString(false, kpff.Value));
                    pwe.Strings.Set("Form field " + kpff.Name + " type", new ProtectedString(false, "checkbox"));
                }
                else if (kpff.Type == FormFieldType.FFTradio)
                {
                    pwe.Strings.Set("Form field " + kpff.Name + " value", new ProtectedString(false, kpff.Value));
                    pwe.Strings.Set("Form field " + kpff.Name + " type", new ProtectedString(false, "radio"));
                }
                else if (kpff.Type == FormFieldType.FFTselect)
                {
                    pwe.Strings.Set("Form field " + kpff.Name + " value", new ProtectedString(false, kpff.Value));
                    pwe.Strings.Set("Form field " + kpff.Name + " type", new ProtectedString(false, "select"));
                }

                pwe.Strings.Set("Form field " + kpff.Name + " page", new ProtectedString(false, kpff.Page.ToString()));

                if (kpff.Id != null && kpff.Id.Length > 0)
                    pwe.Strings.Set("Form field " + kpff.Name + " id", new ProtectedString(false, kpff.Id));
            }

            string altURLs = "";

            for (int i = 0; i < login.URLs.Length; i++)
            {
                string url = login.URLs[i];
                if (i == 0)
                    pwe.Strings.Set("URL", new ProtectedString(host.Database.MemoryProtection.ProtectUrl, url ?? ""));
                else if (i == 1)
                    altURLs += url;
                else
                    altURLs += " " + url;
            }
            if (altURLs.Length > 0)
                pwe.Strings.Set("Alternative URLs", new ProtectedString(host.Database.MemoryProtection.ProtectUrl, altURLs));

            pwe.Strings.Set("Form match URL", new ProtectedString(host.Database.MemoryProtection.ProtectUrl, login.FormActionURL ?? ""));
            pwe.Strings.Set("Form HTTP realm", new ProtectedString(host.Database.MemoryProtection.ProtectUrl, login.HTTPRealm ?? ""));

            // Set some of the string fields
            pwe.Strings.Set(PwDefs.TitleField, new ProtectedString(host.Database.MemoryProtection.ProtectTitle, login.Title ?? ""));

            // update the icon for this entry (in most cases we'll 
            // just detect that it is the same standard icon as before)
            PwUuid customIconUUID = PwUuid.Zero;
            PwIcon iconId = PwIcon.Key;
            if (login.IconImageData != null
                && login.IconImageData.Length > 0
                && base64ToIcon(login.IconImageData, ref customIconUUID, ref iconId))
            {
                if (customIconUUID == PwUuid.Zero)
                    pwe.IconId = iconId;
                else
                    pwe.CustomIconUuid = customIconUUID;
            }
        }


        /// <summary>
        /// extract the current icon information for this entry
        /// </summary>
        /// <param name="customIconUUID"></param>
        /// <param name="iconId"></param>
        /// <returns></returns>
        private string iconToBase64(PwUuid customIconUUID, PwIcon iconId)
        {
            Image icon = null;
            string imageData = "";
            if (customIconUUID != PwUuid.Zero)
            {
                icon = host.Database.GetCustomIcon(customIconUUID);
                if (icon == null)
                    icon = host.MainWindow.ClientIcons.Images[(int)iconId];
            }
            else
            {
                icon = host.MainWindow.ClientIcons.Images[(int)iconId];
            }

            if (icon != null)
            {
                MemoryStream ms = new MemoryStream();
                icon.Save(ms, System.Drawing.Imaging.ImageFormat.Png);
                //Encoding.UTF8.GetBytes
                imageData = Convert.ToBase64String(ms.ToArray());
            }

            return imageData;
        }

        /// <summary>
        /// converts a string to the relevant icon for this entry
        /// </summary>
        /// <param name="imageData">base64 representation of the image</param>
        /// <param name="customIconUUID">UUID of the generated custom icon; may be Zero</param>
        /// <param name="iconId">PwIcon of the matched standard icon; ignore if customIconUUID != Zero</param>
        /// <returns>true if the supplied imageData was converted into a customIcon 
        /// or matched with a standard icon.</returns>
        private bool base64ToIcon(string imageData, ref PwUuid customIconUUID, ref PwIcon iconId)
        {
            iconId = PwIcon.Key;
            customIconUUID = PwUuid.Zero;

            for (int i = 0; i < _standardIconsBase64.Length; i++)
            {
                string item = _standardIconsBase64[i];
                if (item == imageData)
                {
                    iconId = (PwIcon)i;
                    return true;
                }
            }

            try
            {
                //MemoryStream id = new MemoryStream();
                //icon.Save(ms, System.Drawing.Imaging.ImageFormat.Png);

                Image img = KeePass.UI.UIUtil.LoadImage(Convert.FromBase64String(imageData));

                Image imgNew = new Bitmap(img, new Size(16, 16));

                MemoryStream ms = new MemoryStream();
                imgNew.Save(ms, System.Drawing.Imaging.ImageFormat.Png);

                PwCustomIcon pwci = new PwCustomIcon(new PwUuid(true),
                    ms.ToArray());
                host.Database.CustomIcons.Add(pwci);

                customIconUUID = pwci.Uuid;
                host.Database.UINeedsIconUpdate = true;

                return true;
            }
            catch
            {
                return false;
            }
        }

        #endregion

        #region Configuration of KeePass/KeeFox and databases

        [JsonRpcMethod]
        public Configuration GetCurrentKFConfig()
        {
            bool autoCommit = host.CustomConfig.GetBool("KeePassRPC.KeeFox.autoCommit", true);
            string[] MRUList = new string[host.MainWindow.FileMruList.ItemCount];
            for (uint i = 0; i < host.MainWindow.FileMruList.ItemCount; i++)
                MRUList[i] = ((IOConnectionInfo)host.MainWindow.FileMruList.GetItem(i).Value).Path;

            Configuration currentConfig = new Configuration(MRUList, autoCommit);
            return currentConfig;
        }


        //public bool SetCurrentKFConfig(Configuration config)
        //{
        //    host.CustomConfig.SetBool("KeeICE.KeeFox.autoCommit", config.AutoCommit);
        //    host.MainWindow.Invoke((MethodInvoker)delegate { host.MainWindow.SaveConfig(); });
        //    return true;
        //}

        //public bool setCurrentDBRootGroup(string uuid)
        //{
        //    if (!host.Database.IsOpen)
        //        return false;

        //    host.Database.CustomData.Set("KeeICE.KeeFox.rootUUID", uuid);
        //    saveDB();

        //    return true;
        //}


        #endregion

        #region Retrival and manipulation of databases and the KeePass app

        [JsonRpcMethod]
        public string GetDatabaseName()
        {
            if (!host.Database.IsOpen)
                return "";
            return (host.Database.Name.Length > 0 ? host.Database.Name : "no name");
        }

        [JsonRpcMethod]
        public string GetDatabaseFileName()
        {
            return host.Database.IOConnectionInfo.Path;
        }

        /// <summary>
        /// changes current active database
        /// </summary>
        /// <param name="fileName">Path to database to open. If empty, user is prompted to choose a file</param>
        /// <param name="closeCurrent">if true, currently active database is closed first. if false,
        /// both stay open with fileName DB active</param>
        [JsonRpcMethod]
        public void ChangeDatabase(string fileName, bool closeCurrent)
        {
            if (closeCurrent && host.MainWindow.DocumentManager.ActiveDatabase != null)
            {
                host.MainWindow.DocumentManager.CloseDatabase(host.MainWindow.DocumentManager.ActiveDatabase);
            }

            KeePassLib.Serialization.IOConnectionInfo ioci = null;

            if (fileName != null && fileName.Length > 0)
            {
                ioci = new KeePassLib.Serialization.IOConnectionInfo();
                ioci.Path = fileName;
            }

            host.MainWindow.Invoke((MethodInvoker)delegate { host.MainWindow.OpenDatabase(ioci, null, false); });
            return;
        }

        [JsonRpcMethod]
        public string GeneratePassword(string profileName)
        {
            //KeePass.Program.PwGeneratorPool
            // KeePass.Util.PwGeneratorUtil.
            //foreach (PwProfile pwgo in Program.Config.PasswordGenerator.UserProfiles)
            //{
            //    if (pwgo.Name == strProfile)
            //    {
            //        SetGenerationOptions(pwgo);
            //        break;
            //    }
            //}
            return "password";
        }

        #endregion
        
        #region Retrival and manipulation of entries and groups

        /// <summary>
        /// removes a single entry from the database
        /// </summary>
        /// <param name="uuid">The unique indentifier of the entry we want to remove</param>
        /// <returns>true if entry removed successfully, false if it failed</returns>
        [JsonRpcMethod]
        public bool RemoveEntry(string uuid)
        {
            // Make sure there is an active database
            if (!ensureDBisOpen()) return false;

            if (uuid != null && uuid.Length > 0)
            {
                PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(uuid));

                PwEntry matchedLogin = GetRootPwGroup().FindEntry(pwuuid, true);

                if (matchedLogin == null)
                    throw new Exception("Could not find requested entry.");

                PwGroup matchedLoginParent = matchedLogin.ParentGroup;
                if (matchedLoginParent == null) return false; // Can't remove

                matchedLoginParent.Entries.Remove(matchedLogin);

                PwGroup recycleBin = host.Database.RootGroup.FindGroup(host.Database.RecycleBinUuid, true);

                if (host.Database.RecycleBinEnabled == false)
                {
                    if (!KeePassLib.Utility.MessageService.AskYesNo(KPRes.DeleteEntriesQuestionSingle, KPRes.DeleteEntriesTitleSingle))
                        return false;

                    PwDeletedObject pdo = new PwDeletedObject();
                    pdo.Uuid = matchedLogin.Uuid;
                    pdo.DeletionTime = DateTime.Now;
                    host.Database.DeletedObjects.Add(pdo);
                }
                else
                {
                    if (recycleBin == null)
                    {
                        recycleBin = new PwGroup(true, true, KPRes.RecycleBin, PwIcon.TrashBin);
                        recycleBin.EnableAutoType = false;
                        recycleBin.EnableSearching = false;
                        host.Database.RootGroup.AddGroup(recycleBin, true);

                        host.Database.RecycleBinUuid = recycleBin.Uuid;
                    }

                    recycleBin.AddEntry(matchedLogin, true);
                    matchedLogin.Touch(false);
                }

                //matchedLogin.ParentGroup.Entries.Remove(matchedLogin);
                host.MainWindow.BeginInvoke(new MethodInvoker(saveDB));

                return true;
            }
            return false;
        }

        /// <summary>
        /// removes a single group and its contents from the database
        /// </summary>
        /// <param name="uuid">The unique indentifier of the group we want to remove</param>
        /// <returns>true if group removed successfully, false if it failed</returns>
        [JsonRpcMethod]
        public bool RemoveGroup(string uuid)
        {
            // Make sure there is an active database
            if (!ensureDBisOpen()) return false;

            if (uuid != null && uuid.Length > 0)
            {
                PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(uuid));

                PwGroup matchedGroup = GetRootPwGroup().FindGroup(pwuuid, true);

                if (matchedGroup == null)
                    throw new Exception("Could not find requested entry.");

                PwGroup matchedGroupParent = matchedGroup.ParentGroup;
                if (matchedGroupParent == null) return false; // Can't remove

                matchedGroupParent.Groups.Remove(matchedGroup);

                PwGroup recycleBin = host.Database.RootGroup.FindGroup(host.Database.RecycleBinUuid, true);

                if (host.Database.RecycleBinEnabled == false)
                {
                    if (!KeePassLib.Utility.MessageService.AskYesNo(KPRes.DeleteGroupQuestion, KPRes.DeleteGroupTitle))
                        return false;

                    PwDeletedObject pdo = new PwDeletedObject();
                    pdo.Uuid = matchedGroup.Uuid;
                    pdo.DeletionTime = DateTime.Now;
                    host.Database.DeletedObjects.Add(pdo);
                }
                else
                {
                    if (recycleBin == null)
                    {
                        recycleBin = new PwGroup(true, true, KPRes.RecycleBin, PwIcon.TrashBin);
                        recycleBin.EnableAutoType = false;
                        recycleBin.EnableSearching = false;
                        host.Database.RootGroup.AddGroup(recycleBin, true);

                        host.Database.RecycleBinUuid = recycleBin.Uuid;
                    }

                    recycleBin.AddGroup(matchedGroup, true);
                    matchedGroup.Touch(false);
                }

                host.MainWindow.BeginInvoke(new MethodInvoker(saveDB));

                return true;
            }
            return false;
        }

        /// <summary>
        /// Add a new password/login to the active KeePass database
        /// </summary>
        /// <param name="login">The KeeICE representation of the login to be added</param>
        /// <param name="parentUUID">The UUID of the parent group for the new login. If null, the root group will be used.</param>
        /// <param name="current__"></param>
        [JsonRpcMethod]
        public Entry AddLogin(Entry login, string parentUUID)
        {
            // Make sure there is an active database
            if (!ensureDBisOpen()) return null;

            PwEntry newLogin = new PwEntry(true, true);

            setPwEntryFromEntry(newLogin, login);

            PwGroup parentGroup = GetRootPwGroup(); // if in doubt we'll stick it in the root folder

            if (parentUUID != null && parentUUID.Length > 0)
            {
                PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(parentUUID));

                PwGroup matchedGroup = GetRootPwGroup().FindGroup(pwuuid, true);

                if (matchedGroup != null)
                    parentGroup = matchedGroup;
            }

            parentGroup.AddEntry(newLogin, true);

            host.MainWindow.BeginInvoke(new MethodInvoker(saveDB));

            Entry output = GetEntryFromPwEntry(newLogin, true);

            return output;
        }

        /// <summary>
        /// Add a new group/folder to the active KeePass database
        /// </summary>
        /// <param name="name">The name of the group to be added</param>
        /// <param name="parentUUID">The UUID of the parent group for the new group. If null, the root group will be used.</param>
        /// <param name="current__"></param>
        [JsonRpcMethod]
        public Group AddGroup(string name, string parentUUID)
        {
            // Make sure there is an active database
            if (!ensureDBisOpen()) return null;

            PwGroup newGroup = new PwGroup(true, true);
            newGroup.Name = name;

            PwGroup parentGroup = GetRootPwGroup(); // if in doubt we'll stick it in the root folder

            if (parentUUID != null && parentUUID.Length > 0)
            {
                PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(parentUUID));

                PwGroup matchedGroup = host.Database.RootGroup.Uuid == pwuuid ? host.Database.RootGroup : host.Database.RootGroup.FindGroup(pwuuid, true);

                if (matchedGroup != null)
                    parentGroup = matchedGroup;
            }

            parentGroup.AddGroup(newGroup, true);

            host.MainWindow.BeginInvoke(new MethodInvoker(saveDB));

            Group output = GetGroupFromPwGroup(newGroup);

            return output;
        }

        /// <summary>
        /// Modify an existing login
        /// </summary>
        /// <param name="oldLogin">The old login that will be replaced. In fact only the UUID contained within it will be used for now.</param>
        /// <param name="newLogin">The login object that will replace the old one.</param>
        /// <param name="current__"></param>
        [JsonRpcMethod]
        public void ModifyLogin(Entry oldLogin, Entry newLogin)
        {
            if (oldLogin == null)
                throw new Exception("old login must be passed to the ModifyLogin function. It wasn't");
            if (newLogin == null)
                throw new Exception("new login must be passed to the ModifyLogin function. It wasn't");
            if (oldLogin.UniqueID == null || oldLogin.UniqueID == "")
                throw new Exception("old login doesn't contain a uniqueID");

            // Make sure there is an active database
            if (!ensureDBisOpen()) return;

            PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(oldLogin.UniqueID));

            PwEntry modificationTarget = GetRootPwGroup().FindEntry(pwuuid, true);

            if (modificationTarget == null)
                throw new Exception("Could not find correct entry to modify. No changes made to KeePass database.");

            setPwEntryFromEntry(modificationTarget, newLogin);

            host.MainWindow.BeginInvoke(new MethodInvoker(saveDB));
        }

        /// <summary>
        /// Return the parent group of the object with the supplied UUID
        /// </summary>
        /// <param name="uuid">the UUID of the object we want to find the parent of</param>
        /// <param name="current__"></param>
        /// <returns>the parent group</returns>
        [JsonRpcMethod]
        public Group GetParent(string uuid)
        {
            Group output;

            // Make sure there is an active database
            if (!ensureDBisOpen()) return null;

            PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(uuid));
            PwGroup rootGroup = GetRootPwGroup();

            try
            {

                PwEntry thisEntry = rootGroup.FindEntry(pwuuid, true);
                if (thisEntry != null && thisEntry.ParentGroup != null)
                {
                    output = GetGroupFromPwGroup(thisEntry.ParentGroup);
                    return output;
                }

                PwGroup thisGroup = rootGroup.FindGroup(pwuuid, true);
                if (thisGroup != null && thisGroup.ParentGroup != null)
                {
                    output = GetGroupFromPwGroup(thisGroup.ParentGroup);
                    return output;
                }
            }
            catch (Exception)
            {
                return null;
            }
            output = GetGroupFromPwGroup(rootGroup);
            return output;
        }

        /// <summary>
        /// Return the root group of the active database
        /// </summary>
        /// <param name="current__"></param>
        /// <returns>the root group</returns>
        [JsonRpcMethod]
        public Group GetRoot()
        {
            return GetGroupFromPwGroup(GetRootPwGroup());
        }

        /// <summary>
        /// Return the root group of the active database
        /// </summary>
        /// <returns>the root group</returns>
        [JsonRpcMethod]
        public PwGroup GetRootPwGroup()
        {
            // Make sure there is an active database
            if (!ensureDBisOpen()) { return null; }

            if (host.Database.CustomData.Exists("KeePassRPC.KeeFox.rootUUID") && host.Database.CustomData.Get("KeePassRPC.KeeFox.rootUUID").Length >= 30) //TODO: tighten
            {
                string uuid = host.Database.CustomData.Get("KeePassRPC.KeeFox.rootUUID");

                PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(uuid));

                PwGroup matchedGroup = host.Database.RootGroup.Uuid == pwuuid ? host.Database.RootGroup : host.Database.RootGroup.FindGroup(pwuuid, true);

                if (matchedGroup == null)
                    throw new Exception("Could not find requested group.");

                return matchedGroup;
            }
            else
            {
                return host.Database.RootGroup;
            }
        }

        /// <summary>
        /// Return a list of every login in the database
        /// </summary>
        /// <param name="logins">the list of all logins</param>
        /// <param name="current__"></param>
        /// <returns>the number of logins in the list</returns>
        [JsonRpcMethod]
        public Entry[] GetAllLogins()
        {
            int count = 0;
            ArrayList allEntries = new ArrayList();

            // Make sure there is an active database
            if (!ensureDBisOpen()) { return null; }

            KeePassLib.Collections.PwObjectList<PwEntry> output;
            output = GetRootPwGroup().GetEntries(true);

            foreach (PwEntry pwe in output)
            {
                if (host.Database.RecycleBinUuid.EqualsValue(pwe.ParentGroup.Uuid))
                    continue; // ignore if it's in the recycle bin

                if (pwe.Strings.Exists("Hide from KeeFox") || string.IsNullOrEmpty(pwe.Strings.ReadSafe("URL")))
                    continue;

                Entry kpe = GetEntryFromPwEntry(pwe, false);
                allEntries.Add(kpe);
                count++;

            }

            return (Entry[])allEntries.ToArray(typeof(Entry));
        }

        /// <summary>
        /// Returns a list of every entry contained within a group (not recursive)
        /// </summary>
        /// <param name="uuid">the unique ID of the group we're interested in.</param>
        /// <param name="current__"></param>
        /// <returns>the list of every entry directly inside the group.</returns>
        [JsonRpcMethod]
        public Entry[] GetChildEntries(string uuid)
        {
            Entry[] entries = null;
            ArrayList allEntries = new ArrayList();

            if (uuid != null && uuid.Length > 0)
            {
                // Make sure there is an active database
                if (!ensureDBisOpen()) { return null; }

                PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(uuid));

                PwGroup matchedGroup = host.Database.RootGroup.Uuid == pwuuid ? host.Database.RootGroup : host.Database.RootGroup.FindGroup(pwuuid, true);

                if (matchedGroup == null)
                    throw new Exception("Could not find requested group.");

                KeePassLib.Collections.PwObjectList<PwEntry> output;
                output = matchedGroup.GetEntries(false);

                foreach (PwEntry pwe in output)
                {
                    if (host.Database.RecycleBinUuid.EqualsValue(pwe.ParentGroup.Uuid))
                        continue; // ignore if it's in the recycle bin

                    if (pwe.Strings.Exists("Hide from KeeFox") || string.IsNullOrEmpty(pwe.Strings.ReadSafe("URL")))
                        continue;

                    Entry kpe = GetEntryFromPwEntry(pwe, false);
                    allEntries.Add(kpe);
                }

                entries = (Entry[])allEntries.ToArray(typeof(Entry));
            }

            return entries;
        }

        /// <summary>
        /// Returns a list of every group contained within a group (not recursive)
        /// </summary>
        /// <param name="uuid">the unique ID of the group we're interested in.</param>
        /// <param name="current__"></param>
        /// <returns>the list of every group directly inside the group.</returns>
        [JsonRpcMethod]
        public Group[] GetChildGroups(string uuid)
        {
            Group[] entries = null;
            ArrayList allGroups = new ArrayList();

            PwGroup matchedGroup;

            // Make sure there is an active database
            if (!ensureDBisOpen()) { return null; }

            if (uuid != null && uuid.Length > 0)
            {
                PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(uuid));

                matchedGroup = host.Database.RootGroup.Uuid == pwuuid ? host.Database.RootGroup : host.Database.RootGroup.FindGroup(pwuuid, true);
            }
            else
            {
                matchedGroup = GetRootPwGroup();
            }

            if (matchedGroup == null)
                throw new Exception("Could not find requested group.");

            KeePassLib.Collections.PwObjectList<PwGroup> output;
            output = matchedGroup.Groups;

            foreach (PwGroup pwg in output)
            {
                if (host.Database.RecycleBinUuid.EqualsValue(pwg.Uuid))
                    continue; // ignore if it's the recycle bin

                Group kpg = GetGroupFromPwGroup(pwg);
                allGroups.Add(kpg);
            }

            entries = (Group[])allGroups.ToArray(typeof(Group));
            return entries;
        }

        /// <summary>
        /// Return a list of groups. If uuid is supplied, the list will have a maximum of one entry. Otherwise it could have any number. TODO: KeePass doesn't have an easy way to search groups by name so postponing that functionality until really needed (or implemented by KeePass API anyway) - for now, name IS COMPLETELY IGNORED
        /// </summary>
        /// <param name="name">IGNORED! The name of a groups we are looking for. Must be an exact match.</param>
        /// <param name="uuid">The UUID of the group we are looking for.</param>
        /// <param name="groups">The output result (a list of Groups)</param>
        /// <param name="current__"></param>
        /// <returns>The number of items in the list of groups.</returns>
        [JsonRpcMethod]
        public int FindGroups(string name, string uuid, out Group[] groups)
        {
            // if uniqueID is supplied, match just that one group. if not found, move on to search the content of the logins...
            if (uuid != null && uuid.Length > 0)
            {
                // Make sure there is an active database
                if (!ensureDBisOpen()) { groups = null; return -1; }

                PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(uuid));

                PwGroup matchedGroup = host.Database.RootGroup.Uuid == pwuuid ? host.Database.RootGroup : host.Database.RootGroup.FindGroup(pwuuid, true);

                if (matchedGroup == null)
                    throw new Exception("Could not find requested group.");

                groups = new Group[1];
                groups[0] = GetGroupFromPwGroup(matchedGroup);
                if (groups[0] != null)
                    return 1;
            }


            groups = null;

            return 0;
        }

        private bool matchesAnyURL(PwEntry pwe, string url)
        {
            if (pwe.Strings.Exists("URL") && pwe.Strings.ReadSafe("URL").Length > 0
                    && (url == "" || pwe.Strings.ReadSafe("URL").Contains(url))
               )
                return true;

            string urls = pwe.Strings.ReadSafe("Alternative URLs");
            string[] urlsArray = urls.Split(new char[' ']);
            foreach (string altURL in urlsArray)
                if (altURL.Contains(url))
                    return true;

            return false;

        }

        [JsonRpcMethod]
        public Entry[] FindLogins(string URL, string actionURL, string httpRealm, LoginSearchType lst, bool requireFullURLMatches, string uniqueID)
        {
            string hostname = URL;
            string actionHost = actionURL;
            
            // Make sure there is an active database
            if (!ensureDBisOpen()) { return null; }

            // if uniqueID is supplied, match just that one login. if not found, move on to search the content of the logins...
            if (uniqueID != null && uniqueID.Length > 0)
            {
                PwUuid pwuuid = new PwUuid(KeePassLib.Utility.MemUtil.HexStringToByteArray(uniqueID));

                PwEntry matchedLogin = GetRootPwGroup().FindEntry(pwuuid, true);

                if (matchedLogin == null)
                    throw new Exception("Could not find requested entry.");

                Entry[] logins = new Entry[1];
                logins[0] = GetEntryFromPwEntry(matchedLogin, true);
                if (logins[0] != null)
                    return logins;
            }

            // make sure that hostname and actionURL always represent only the hostname portion
            // of the URL
            // It's tempting to demand that the protocol must match too (e.g. http forms won't
            // match a stored https login) but best not to define such a restriction in KeePassRPC
            // - the RPC client (e.g. KeeFox) can decide to penalise protocol mismatches, 
            // potentially dependant on user configuration options in the client.
            int protocolIndex = URL.IndexOf("://");
            if (URL.IndexOf("file://") > -1)
            {
                // the "host and port" of a file is the actual file name (i.e. just not the query string)

                int qsIndex = URL.IndexOf("?");
                if (qsIndex > -1)
                    hostname = URL.Substring(8, qsIndex - 8);
                else
                    hostname = URL.Substring(8);
            }
            else if (protocolIndex > -1)
            {
                string hostAndPort = URL.Substring(protocolIndex + 3);
                int pathStart = hostAndPort.IndexOf("/", 0);
                if (pathStart > -1 && hostAndPort.Length > pathStart)
                {
                    hostname = URL.Substring(0, pathStart + protocolIndex + 3);
                }
            }
            else
            {
                // we havn't received a protocol but may still have a query string 
                // we'd like to remove from the URL (e.g. especially if we're dealing with an unknown file:///)
                int qsIndex = URL.IndexOf("?");
                if (qsIndex > -1)
                    hostname = URL.Substring(1, qsIndex - 1);
            }


            protocolIndex = actionURL.IndexOf("://");
            if (protocolIndex > -1)
            {
                string actionURLAndPort = actionURL.Substring(protocolIndex + 3);
                int pathStart = actionURLAndPort.IndexOf("/", 0);
                if (pathStart > -1 && actionURLAndPort.Length > pathStart)
                {
                    actionHost = actionURL.Substring(0, pathStart + protocolIndex + 3);
                }
            }


            int count = 0;
            ArrayList allEntries = new ArrayList();


            // Narrow down the possible matches by doing a KeePass search
            // (We could match on an irrelevant string field but chances are that any matches are suitable)
            SearchParameters sp = new SearchParameters();
            sp.SearchInUrls = true;
            sp.SearchInOther = true;
            sp.RegularExpression = true;
            if (hostname.Length == 0)
                sp.SearchString = ".*";
            else if (requireFullURLMatches)
                sp.SearchString = System.Text.RegularExpressions.Regex.Escape(URL);
            else
                sp.SearchString = System.Text.RegularExpressions.Regex.Escape(hostname);

            KeePassLib.Collections.PwObjectList<PwEntry> output;
            output = new KeePassLib.Collections.PwObjectList<PwEntry>();

            PwGroup searchGroup = GetRootPwGroup();
            searchGroup.SearchEntries(sp, output, false);
            foreach (PwEntry pwe in output)
            {
                if (host.Database.RecycleBinUuid.EqualsValue(pwe.ParentGroup.Uuid))
                    continue; // ignore if it's in the recycle bin

                if (pwe.Strings.Exists("Hide from KeeFox") || string.IsNullOrEmpty(pwe.Strings.ReadSafe("URL")))
                    continue;

                bool entryIsAMatch = false;
                bool entryIsAnExactMatch = false;

                if (lst != LoginSearchType.LSTnoForms && matchesAnyURL(pwe, hostname))
                {
                    if (pwe.Strings.Exists("Form match URL") && pwe.Strings.ReadSafe("Form match URL") == actionURL && pwe.Strings.ReadSafe("URL") == URL)
                    {
                        entryIsAnExactMatch = true;
                        entryIsAMatch = true;
                    }
                    else if (!requireFullURLMatches)
                        entryIsAMatch = true;
                }

                if (lst != LoginSearchType.LSTnoRealms && matchesAnyURL(pwe, hostname))
                {
                    if (pwe.Strings.Exists("Form HTTP realm") && pwe.Strings.ReadSafe("Form HTTP realm").Length > 0
                    && (httpRealm == "" || pwe.Strings.ReadSafe("Form HTTP realm") == httpRealm)
                    && pwe.Strings.ReadSafe("URL") == URL)
                    {
                        entryIsAnExactMatch = true;
                        entryIsAMatch = true;
                    }
                    else if (!requireFullURLMatches)
                        entryIsAMatch = true;
                }

                if (entryIsAMatch)
                {
                    Entry kpe = GetEntryFromPwEntry(pwe, entryIsAnExactMatch);
                    allEntries.Add(kpe);
                    count++;
                }

            }

            return (Entry[])allEntries.ToArray(typeof(Entry));
        }


        [JsonRpcMethod]
        public int CountLogins(string URL, string actionURL, string httpRealm, LoginSearchType lst, bool requireFullURLMatches)
        {
            string hostname = URL;
            string actionHost = actionURL;

            // make sure that hostname and actionURL always represent only the hostname portion
            // of the URL

            int protocolIndex = URL.IndexOf("://");
            if (URL.IndexOf("file://") > -1)
            {
                // the "host and port" of a file is the actual file name (i.e. just not the query string)

                int qsIndex = URL.IndexOf("?");
                if (qsIndex > -1)
                    hostname = URL.Substring(8, qsIndex - 8);
                else
                    hostname = URL.Substring(8);
            }
            else if (protocolIndex > -1)
            {
                string hostAndPort = URL.Substring(protocolIndex + 3);
                int pathStart = hostAndPort.IndexOf("/", 0);
                if (pathStart > -1 && hostAndPort.Length > pathStart)
                {
                    hostname = URL.Substring(0, pathStart + protocolIndex + 3);
                }
            }
            else
            {
                // we havn't received a protocol but may still have a query string 
                // we'd like to remove from the URL (e.g. especially if we're dealing with a file:///
                int qsIndex = URL.IndexOf("?");
                if (qsIndex > -1)
                    hostname = URL.Substring(1, qsIndex - 1);
            }

            protocolIndex = actionURL.IndexOf("://");
            if (protocolIndex > -1)
            {
                string actionURLAndPort = actionURL.Substring(protocolIndex + 3);
                int pathStart = actionURLAndPort.IndexOf("/", 0);
                if (pathStart > -1 && actionURLAndPort.Length > pathStart)
                {
                    actionHost = actionURL.Substring(0, pathStart + protocolIndex + 3);
                }
            }

            int count = 0;
            ArrayList allEntries = new ArrayList();


            // Make sure there is an active database
            if (!ensureDBisOpen()) return -1;

            // Narrow down the possible matches by doing a KeePass search
            // (We could match on an irrelevant string field but chances are that any matches are suitable)
            SearchParameters sp = new SearchParameters();
            sp.SearchInUrls = true;
            sp.SearchInOther = true;
            sp.RegularExpression = true;
            if (URL.Length == 0)
                sp.SearchString = ".*";
            else if (requireFullURLMatches)
                sp.SearchString = System.Text.RegularExpressions.Regex.Escape(URL);
            else
                sp.SearchString = System.Text.RegularExpressions.Regex.Escape(hostname);

            KeePassLib.Collections.PwObjectList<PwEntry> output;
            output = new KeePassLib.Collections.PwObjectList<PwEntry>();

            PwGroup searchGroup = GetRootPwGroup();
            searchGroup.SearchEntries(sp, output, false);
            foreach (PwEntry pwe in output)
            {
                if (host.Database.RecycleBinUuid.EqualsValue(pwe.ParentGroup.Uuid))
                    continue; // ignore if it's in the recycle bin

                if (pwe.Strings.Exists("Hide from KeeFox") || string.IsNullOrEmpty(pwe.Strings.ReadSafe("URL")))
                    continue;

                bool entryIsAMatch = false;

                if (lst != LoginSearchType.LSTnoForms && matchesAnyURL(pwe, hostname))
                {
                    if (pwe.Strings.Exists("Form match URL") && pwe.Strings.ReadSafe("Form match URL") == actionURL && pwe.Strings.ReadSafe("URL") == URL)
                    {
                        entryIsAMatch = true;
                    }
                    else if (!requireFullURLMatches)
                        entryIsAMatch = true;
                }

                if (lst != LoginSearchType.LSTnoRealms && matchesAnyURL(pwe, hostname))
                {
                    if (pwe.Strings.Exists("Form HTTP realm") && pwe.Strings.ReadSafe("Form HTTP realm").Length > 0
                    && (httpRealm == "" || pwe.Strings.ReadSafe("Form HTTP realm") == httpRealm)
                    && pwe.Strings.ReadSafe("URL") == URL)
                    {
                        entryIsAMatch = true;
                    }
                    else if (!requireFullURLMatches)
                        entryIsAMatch = true;
                }

                if (entryIsAMatch)
                    count++;

            }
            


            return count;
        }

        #endregion

    }
}