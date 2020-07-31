/* ========================================================================
 * Copyright (c) 2005-2019 The OPC Foundation, Inc. All rights reserved.
 *
 * OPC Foundation MIT License 1.00
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * The complete license agreement can be found here:
 * http://opcfoundation.org/License/MIT/1.00/
 * ======================================================================*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Runtime.Serialization;
using Opc.Ua;
using Opc.Ua.Skills;
using ExampleLinearAxisWithGripper;
using Opc.Ua.Di;

namespace MyCompany
{
    #region MyFancyAxisState Class
    #if (!OPCUA_EXCLUDE_MyFancyAxisState)
    /// <summary>
    /// Stores an instance of the MyFancyAxisType ObjectType.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public partial class MyFancyAxisState : DeviceState
    {
        #region Constructors
        /// <summary>
        /// Initializes the type with its default attribute values.
        /// </summary>
        public MyFancyAxisState(NodeState parent) : base(parent)
        {
        }

        /// <summary>
        /// Returns the id of the default type definition node for the instance.
        /// </summary>
        protected override NodeId GetDefaultTypeDefinitionId(NamespaceTable namespaceUris)
        {
            return Opc.Ua.NodeId.Create(MyCompany.ObjectTypes.MyFancyAxisType, MyCompany.Namespaces.MyCompany, namespaceUris);
        }

        #if (!OPCUA_EXCLUDE_InitializationStrings)
        /// <summary>
        /// Initializes the instance.
        /// </summary>
        protected override void Initialize(ISystemContext context)
        {
            Initialize(context, InitializationString);
            InitializeOptionalChildren(context);
        }

        /// <summary>
        /// Initializes the instance with a node.
        /// </summary>
        protected override void Initialize(ISystemContext context, NodeState source)
        {
            InitializeOptionalChildren(context);
            base.Initialize(context, source);
        }

        /// <summary>
        /// Initializes the any option children defined for the instance.
        /// </summary>
        protected override void InitializeOptionalChildren(ISystemContext context)
        {
            base.InitializeOptionalChildren(context);
        }

        #region Initialization String
        private const string InitializationString =
           "BAAAACEAAABodHRwczovL2V4YW1wbGUuY29tL1VBL015Q29tcGFueS8jAAAAaHR0cDovL29wY2ZvdW5k" +
           "YXRpb24ub3JnL1VBL1NraWxscy82AAAAaHR0cHM6Ly9leGFtcGxlLmNvbS9VQS9FeGFtcGxlcy9MaW5l" +
           "YXJBeGlzV2l0aEdyaXBwZXIvHwAAAGh0dHA6Ly9vcGNmb3VuZGF0aW9uLm9yZy9VQS9ESS//////BGCA" +
           "AgEAAAABABcAAABNeUZhbmN5QXhpc1R5cGVJbnN0YW5jZQEBmToBAZk6mToAAP////8IAAAANWCJCgIA" +
           "AAAEAAwAAABNYW51ZmFjdHVyZXIBAbA6AwAAAAAwAAAATmFtZSBvZiB0aGUgY29tcGFueSB0aGF0IG1h" +
           "bnVmYWN0dXJlZCB0aGUgZGV2aWNlAC4ARLA6AAAAFf////8BAf////8AAAAANWCJCgIAAAAEAAUAAABN" +
           "b2RlbAEBsjoDAAAAABgAAABNb2RlbCBuYW1lIG9mIHRoZSBkZXZpY2UALgBEsjoAAAAV/////wEB////" +
           "/wAAAAA1YIkKAgAAAAQAEAAAAEhhcmR3YXJlUmV2aXNpb24BAbM6AwAAAAAsAAAAUmV2aXNpb24gbGV2" +
           "ZWwgb2YgdGhlIGhhcmR3YXJlIG9mIHRoZSBkZXZpY2UALgBEszoAAAAM/////wEB/////wAAAAA1YIkK" +
           "AgAAAAQAEAAAAFNvZnR3YXJlUmV2aXNpb24BAbQ6AwAAAAA1AAAAUmV2aXNpb24gbGV2ZWwgb2YgdGhl" +
           "IHNvZnR3YXJlL2Zpcm13YXJlIG9mIHRoZSBkZXZpY2UALgBEtDoAAAAM/////wEB/////wAAAAA1YIkK" +
           "AgAAAAQADgAAAERldmljZVJldmlzaW9uAQG1OgMAAAAAJAAAAE92ZXJhbGwgcmV2aXNpb24gbGV2ZWwg" +
           "b2YgdGhlIGRldmljZQAuAES1OgAAAAz/////AQH/////AAAAADVgiQoCAAAABAAMAAAARGV2aWNlTWFu" +
           "dWFsAQG3OgMAAAAAWgAAAEFkZHJlc3MgKHBhdGhuYW1lIGluIHRoZSBmaWxlIHN5c3RlbSBvciBhIFVS" +
           "TCB8IFdlYiBhZGRyZXNzKSBvZiB1c2VyIG1hbnVhbCBmb3IgdGhlIGRldmljZQAuAES3OgAAAAz/////" +
           "AQH/////AAAAADVgiQoCAAAABAAMAAAAU2VyaWFsTnVtYmVyAQG5OgMAAAAATQAAAElkZW50aWZpZXIg" +
           "dGhhdCB1bmlxdWVseSBpZGVudGlmaWVzLCB3aXRoaW4gYSBtYW51ZmFjdHVyZXIsIGEgZGV2aWNlIGlu" +
           "c3RhbmNlAC4ARLk6AAAADP////8BAf////8AAAAANWCJCgIAAAAEAA8AAABSZXZpc2lvbkNvdW50ZXIB" +
           "Abs6AwAAAABpAAAAQW4gaW5jcmVtZW50YWwgY291bnRlciBpbmRpY2F0aW5nIHRoZSBudW1iZXIgb2Yg" +
           "dGltZXMgdGhlIHN0YXRpYyBkYXRhIHdpdGhpbiB0aGUgRGV2aWNlIGhhcyBiZWVuIG1vZGlmaWVkAC4A" +
           "RLs6AAAABv////8BAf////8AAAAA";
        #endregion
        #endif
        #endregion

        #region Public Properties
        #endregion

        #region Overridden Methods
        #endregion

        #region Private Fields
        #endregion
    }
    #endif
    #endregion
}