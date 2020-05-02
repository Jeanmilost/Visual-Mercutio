﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.42
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Web.Services;
using System.Web.Services.Protocols;
using System.Xml.Serialization;

// 
// This source code was auto-generated by wsdl, Version=2.0.50727.42.
// 


/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("wsdl", "2.0.50727.42")]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Web.Services.WebServiceBindingAttribute(Name="rpcrouterSoapBinding", Namespace="urn:MessagesSOAP")]
public partial class MessagesSOAPService : System.Web.Services.Protocols.SoapHttpClientProtocol {
    
    private System.Threading.SendOrPostCallback sendMessageOperationCompleted;
    
    /// <remarks/>
    public MessagesSOAPService() {
        this.Url = "http://192.168.111.135:8080/soap/servlet/rpcrouter";
    }
    
    /// <remarks/>
    public event sendMessageCompletedEventHandler sendMessageCompleted;
    
    /// <remarks/>
    [System.Web.Services.Protocols.SoapRpcMethodAttribute("", RequestNamespace="urn:MessagesSOAP", ResponseNamespace="urn:MessagesSOAP")]
    [return: System.Xml.Serialization.SoapElementAttribute("sendMessageReturn")]
    public int sendMessage(string in0, string in1) {
        object[] results = this.Invoke("sendMessage", new object[] {
                    in0,
                    in1});
        return ((int)(results[0]));
    }
    
    /// <remarks/>
    public System.IAsyncResult BeginsendMessage(string in0, string in1, System.AsyncCallback callback, object asyncState) {
        return this.BeginInvoke("sendMessage", new object[] {
                    in0,
                    in1}, callback, asyncState);
    }
    
    /// <remarks/>
    public int EndsendMessage(System.IAsyncResult asyncResult) {
        object[] results = this.EndInvoke(asyncResult);
        return ((int)(results[0]));
    }
    
    /// <remarks/>
    public void sendMessageAsync(string in0, string in1) {
        this.sendMessageAsync(in0, in1, null);
    }
    
    /// <remarks/>
    public void sendMessageAsync(string in0, string in1, object userState) {
        if ((this.sendMessageOperationCompleted == null)) {
            this.sendMessageOperationCompleted = new System.Threading.SendOrPostCallback(this.OnsendMessageOperationCompleted);
        }
        this.InvokeAsync("sendMessage", new object[] {
                    in0,
                    in1}, this.sendMessageOperationCompleted, userState);
    }
    
    private void OnsendMessageOperationCompleted(object arg) {
        if ((this.sendMessageCompleted != null)) {
            System.Web.Services.Protocols.InvokeCompletedEventArgs invokeArgs = ((System.Web.Services.Protocols.InvokeCompletedEventArgs)(arg));
            this.sendMessageCompleted(this, new sendMessageCompletedEventArgs(invokeArgs.Results, invokeArgs.Error, invokeArgs.Cancelled, invokeArgs.UserState));
        }
    }
    
    /// <remarks/>
    public new void CancelAsync(object userState) {
        base.CancelAsync(userState);
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("wsdl", "2.0.50727.42")]
public delegate void sendMessageCompletedEventHandler(object sender, sendMessageCompletedEventArgs e);

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("wsdl", "2.0.50727.42")]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
public partial class sendMessageCompletedEventArgs : System.ComponentModel.AsyncCompletedEventArgs {
    
    private object[] results;
    
    internal sendMessageCompletedEventArgs(object[] results, System.Exception exception, bool cancelled, object userState) : 
            base(exception, cancelled, userState) {
        this.results = results;
    }
    
    /// <remarks/>
    public int Result {
        get {
            this.RaiseExceptionIfNecessary();
            return ((int)(this.results[0]));
        }
    }
}
