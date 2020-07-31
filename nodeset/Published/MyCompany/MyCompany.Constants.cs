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
using System.Reflection;
using System.Xml;
using System.Runtime.Serialization;
using Opc.Ua;
using Opc.Ua.Skills;
using ExampleLinearAxisWithGripper;
using Opc.Ua.Di;

namespace MyCompany
{
    #region Method Identifiers
    /// <summary>
    /// A class that declares constants for all Methods in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class Methods
    {
        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_InitLock Method.
        /// </summary>
        public const uint MyFancyAxisType_Lock_InitLock = 15015;

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_RenewLock Method.
        /// </summary>
        public const uint MyFancyAxisType_Lock_RenewLock = 15018;

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_ExitLock Method.
        /// </summary>
        public const uint MyFancyAxisType_Lock_ExitLock = 15020;

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_BreakLock Method.
        /// </summary>
        public const uint MyFancyAxisType_Lock_BreakLock = 15022;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_InitLock Method.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_InitLock = 15050;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_RenewLock Method.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_RenewLock = 15053;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_ExitLock Method.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_ExitLock = 15055;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_BreakLock Method.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_BreakLock = 15057;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_InitLock Method.
        /// </summary>
        public const uint MyFancyAxis_Lock_InitLock = 15085;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_RenewLock Method.
        /// </summary>
        public const uint MyFancyAxis_Lock_RenewLock = 15088;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_ExitLock Method.
        /// </summary>
        public const uint MyFancyAxis_Lock_ExitLock = 15090;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_BreakLock Method.
        /// </summary>
        public const uint MyFancyAxis_Lock_BreakLock = 15092;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_InitLock Method.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_InitLock = 15120;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_RenewLock Method.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_RenewLock = 15123;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_ExitLock Method.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_ExitLock = 15125;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_BreakLock Method.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_BreakLock = 15127;
    }
    #endregion

    #region Object Identifiers
    /// <summary>
    /// A class that declares constants for all Objects in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class Objects
    {
        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_NetworkAddress Object.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_NetworkAddress = 15059;

        /// <summary>
        /// The identifier for the MyFancyAxis Object.
        /// </summary>
        public const uint MyFancyAxis = 15071;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_NetworkAddress Object.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_NetworkAddress = 15129;

        /// <summary>
        /// The identifier for the MyFancyAxis_Skills Object.
        /// </summary>
        public const uint MyFancyAxis_Skills = 15141;

        /// <summary>
        /// The identifier for the MyFancyAxis_Skills_GraspSkill Object.
        /// </summary>
        public const uint MyFancyAxis_Skills_GraspSkill = 15142;

        /// <summary>
        /// The identifier for the MyFancyAxis_Skills_ReleaseSkill Object.
        /// </summary>
        public const uint MyFancyAxis_Skills_ReleaseSkill = 15143;

        /// <summary>
        /// The identifier for the MyFancyAxis_Skills_PickSkill Object.
        /// </summary>
        public const uint MyFancyAxis_Skills_PickSkill = 15144;

        /// <summary>
        /// The identifier for the MyFancyAxis_Skills_PlaceSkill Object.
        /// </summary>
        public const uint MyFancyAxis_Skills_PlaceSkill = 15145;
    }
    #endregion

    #region ObjectType Identifiers
    /// <summary>
    /// A class that declares constants for all ObjectTypes in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class ObjectTypes
    {
        /// <summary>
        /// The identifier for the MyFancyAxisType ObjectType.
        /// </summary>
        public const uint MyFancyAxisType = 15001;
    }
    #endregion

    #region Variable Identifiers
    /// <summary>
    /// A class that declares constants for all Variables in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class Variables
    {
        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_Locked Variable.
        /// </summary>
        public const uint MyFancyAxisType_Lock_Locked = 15011;

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_LockingClient Variable.
        /// </summary>
        public const uint MyFancyAxisType_Lock_LockingClient = 15012;

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_LockingUser Variable.
        /// </summary>
        public const uint MyFancyAxisType_Lock_LockingUser = 15013;

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_RemainingLockTime Variable.
        /// </summary>
        public const uint MyFancyAxisType_Lock_RemainingLockTime = 15014;

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_InitLock_InputArguments Variable.
        /// </summary>
        public const uint MyFancyAxisType_Lock_InitLock_InputArguments = 15016;

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_InitLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxisType_Lock_InitLock_OutputArguments = 15017;

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_RenewLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxisType_Lock_RenewLock_OutputArguments = 15019;

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_ExitLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxisType_Lock_ExitLock_OutputArguments = 15021;

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_BreakLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxisType_Lock_BreakLock_OutputArguments = 15023;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_Locked Variable.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_Locked = 15046;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_LockingClient Variable.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_LockingClient = 15047;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_LockingUser Variable.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_LockingUser = 15048;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_RemainingLockTime Variable.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_RemainingLockTime = 15049;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_InitLock_InputArguments Variable.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_InitLock_InputArguments = 15051;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_InitLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_InitLock_OutputArguments = 15052;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_RenewLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_RenewLock_OutputArguments = 15054;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_ExitLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_ExitLock_OutputArguments = 15056;

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_BreakLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxisType_CPIdentifier_Lock_BreakLock_OutputArguments = 15058;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_Locked Variable.
        /// </summary>
        public const uint MyFancyAxis_Lock_Locked = 15081;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_LockingClient Variable.
        /// </summary>
        public const uint MyFancyAxis_Lock_LockingClient = 15082;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_LockingUser Variable.
        /// </summary>
        public const uint MyFancyAxis_Lock_LockingUser = 15083;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_RemainingLockTime Variable.
        /// </summary>
        public const uint MyFancyAxis_Lock_RemainingLockTime = 15084;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_InitLock_InputArguments Variable.
        /// </summary>
        public const uint MyFancyAxis_Lock_InitLock_InputArguments = 15086;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_InitLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxis_Lock_InitLock_OutputArguments = 15087;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_RenewLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxis_Lock_RenewLock_OutputArguments = 15089;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_ExitLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxis_Lock_ExitLock_OutputArguments = 15091;

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_BreakLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxis_Lock_BreakLock_OutputArguments = 15093;

        /// <summary>
        /// The identifier for the MyFancyAxis_Manufacturer Variable.
        /// </summary>
        public const uint MyFancyAxis_Manufacturer = 15094;

        /// <summary>
        /// The identifier for the MyFancyAxis_Model Variable.
        /// </summary>
        public const uint MyFancyAxis_Model = 15096;

        /// <summary>
        /// The identifier for the MyFancyAxis_HardwareRevision Variable.
        /// </summary>
        public const uint MyFancyAxis_HardwareRevision = 15097;

        /// <summary>
        /// The identifier for the MyFancyAxis_SoftwareRevision Variable.
        /// </summary>
        public const uint MyFancyAxis_SoftwareRevision = 15098;

        /// <summary>
        /// The identifier for the MyFancyAxis_DeviceRevision Variable.
        /// </summary>
        public const uint MyFancyAxis_DeviceRevision = 15099;

        /// <summary>
        /// The identifier for the MyFancyAxis_DeviceManual Variable.
        /// </summary>
        public const uint MyFancyAxis_DeviceManual = 15101;

        /// <summary>
        /// The identifier for the MyFancyAxis_SerialNumber Variable.
        /// </summary>
        public const uint MyFancyAxis_SerialNumber = 15103;

        /// <summary>
        /// The identifier for the MyFancyAxis_RevisionCounter Variable.
        /// </summary>
        public const uint MyFancyAxis_RevisionCounter = 15105;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_Locked Variable.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_Locked = 15116;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_LockingClient Variable.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_LockingClient = 15117;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_LockingUser Variable.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_LockingUser = 15118;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_RemainingLockTime Variable.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_RemainingLockTime = 15119;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_InitLock_InputArguments Variable.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_InitLock_InputArguments = 15121;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_InitLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_InitLock_OutputArguments = 15122;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_RenewLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_RenewLock_OutputArguments = 15124;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_ExitLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_ExitLock_OutputArguments = 15126;

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_BreakLock_OutputArguments Variable.
        /// </summary>
        public const uint MyFancyAxis_CPIdentifier_Lock_BreakLock_OutputArguments = 15128;
    }
    #endregion

    #region Method Node Identifiers
    /// <summary>
    /// A class that declares constants for all Methods in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class MethodIds
    {
        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_InitLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_InitLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxisType_Lock_InitLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_RenewLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_RenewLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxisType_Lock_RenewLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_ExitLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_ExitLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxisType_Lock_ExitLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_BreakLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_BreakLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxisType_Lock_BreakLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_InitLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_InitLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxisType_CPIdentifier_Lock_InitLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_RenewLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_RenewLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxisType_CPIdentifier_Lock_RenewLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_ExitLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_ExitLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxisType_CPIdentifier_Lock_ExitLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_BreakLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_BreakLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxisType_CPIdentifier_Lock_BreakLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_InitLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_InitLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxis_Lock_InitLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_RenewLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_RenewLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxis_Lock_RenewLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_ExitLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_ExitLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxis_Lock_ExitLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_BreakLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_BreakLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxis_Lock_BreakLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_InitLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_InitLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxis_CPIdentifier_Lock_InitLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_RenewLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_RenewLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxis_CPIdentifier_Lock_RenewLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_ExitLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_ExitLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxis_CPIdentifier_Lock_ExitLock, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_BreakLock Method.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_BreakLock = new ExpandedNodeId(MyCompany.Methods.MyFancyAxis_CPIdentifier_Lock_BreakLock, MyCompany.Namespaces.MyCompany);
    }
    #endregion

    #region Object Node Identifiers
    /// <summary>
    /// A class that declares constants for all Objects in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class ObjectIds
    {
        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_NetworkAddress Object.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_NetworkAddress = new ExpandedNodeId(MyCompany.Objects.MyFancyAxisType_CPIdentifier_NetworkAddress, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis Object.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis = new ExpandedNodeId(MyCompany.Objects.MyFancyAxis, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_NetworkAddress Object.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_NetworkAddress = new ExpandedNodeId(MyCompany.Objects.MyFancyAxis_CPIdentifier_NetworkAddress, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Skills Object.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Skills = new ExpandedNodeId(MyCompany.Objects.MyFancyAxis_Skills, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Skills_GraspSkill Object.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Skills_GraspSkill = new ExpandedNodeId(MyCompany.Objects.MyFancyAxis_Skills_GraspSkill, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Skills_ReleaseSkill Object.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Skills_ReleaseSkill = new ExpandedNodeId(MyCompany.Objects.MyFancyAxis_Skills_ReleaseSkill, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Skills_PickSkill Object.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Skills_PickSkill = new ExpandedNodeId(MyCompany.Objects.MyFancyAxis_Skills_PickSkill, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Skills_PlaceSkill Object.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Skills_PlaceSkill = new ExpandedNodeId(MyCompany.Objects.MyFancyAxis_Skills_PlaceSkill, MyCompany.Namespaces.MyCompany);
    }
    #endregion

    #region ObjectType Node Identifiers
    /// <summary>
    /// A class that declares constants for all ObjectTypes in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class ObjectTypeIds
    {
        /// <summary>
        /// The identifier for the MyFancyAxisType ObjectType.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType = new ExpandedNodeId(MyCompany.ObjectTypes.MyFancyAxisType, MyCompany.Namespaces.MyCompany);
    }
    #endregion

    #region Variable Node Identifiers
    /// <summary>
    /// A class that declares constants for all Variables in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class VariableIds
    {
        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_Locked Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_Locked = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_Lock_Locked, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_LockingClient Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_LockingClient = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_Lock_LockingClient, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_LockingUser Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_LockingUser = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_Lock_LockingUser, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_RemainingLockTime Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_RemainingLockTime = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_Lock_RemainingLockTime, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_InitLock_InputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_InitLock_InputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_Lock_InitLock_InputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_InitLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_InitLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_Lock_InitLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_RenewLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_RenewLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_Lock_RenewLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_ExitLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_ExitLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_Lock_ExitLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_Lock_BreakLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_Lock_BreakLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_Lock_BreakLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_Locked Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_Locked = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_CPIdentifier_Lock_Locked, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_LockingClient Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_LockingClient = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_CPIdentifier_Lock_LockingClient, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_LockingUser Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_LockingUser = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_CPIdentifier_Lock_LockingUser, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_RemainingLockTime Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_RemainingLockTime = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_CPIdentifier_Lock_RemainingLockTime, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_InitLock_InputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_InitLock_InputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_CPIdentifier_Lock_InitLock_InputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_InitLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_InitLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_CPIdentifier_Lock_InitLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_RenewLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_RenewLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_CPIdentifier_Lock_RenewLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_ExitLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_ExitLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_CPIdentifier_Lock_ExitLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxisType_CPIdentifier_Lock_BreakLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxisType_CPIdentifier_Lock_BreakLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxisType_CPIdentifier_Lock_BreakLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_Locked Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_Locked = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_Lock_Locked, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_LockingClient Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_LockingClient = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_Lock_LockingClient, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_LockingUser Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_LockingUser = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_Lock_LockingUser, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_RemainingLockTime Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_RemainingLockTime = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_Lock_RemainingLockTime, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_InitLock_InputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_InitLock_InputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_Lock_InitLock_InputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_InitLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_InitLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_Lock_InitLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_RenewLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_RenewLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_Lock_RenewLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_ExitLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_ExitLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_Lock_ExitLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Lock_BreakLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Lock_BreakLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_Lock_BreakLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Manufacturer Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Manufacturer = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_Manufacturer, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_Model Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_Model = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_Model, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_HardwareRevision Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_HardwareRevision = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_HardwareRevision, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_SoftwareRevision Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_SoftwareRevision = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_SoftwareRevision, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_DeviceRevision Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_DeviceRevision = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_DeviceRevision, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_DeviceManual Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_DeviceManual = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_DeviceManual, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_SerialNumber Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_SerialNumber = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_SerialNumber, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_RevisionCounter Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_RevisionCounter = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_RevisionCounter, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_Locked Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_Locked = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_CPIdentifier_Lock_Locked, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_LockingClient Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_LockingClient = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_CPIdentifier_Lock_LockingClient, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_LockingUser Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_LockingUser = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_CPIdentifier_Lock_LockingUser, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_RemainingLockTime Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_RemainingLockTime = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_CPIdentifier_Lock_RemainingLockTime, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_InitLock_InputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_InitLock_InputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_CPIdentifier_Lock_InitLock_InputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_InitLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_InitLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_CPIdentifier_Lock_InitLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_RenewLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_RenewLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_CPIdentifier_Lock_RenewLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_ExitLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_ExitLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_CPIdentifier_Lock_ExitLock_OutputArguments, MyCompany.Namespaces.MyCompany);

        /// <summary>
        /// The identifier for the MyFancyAxis_CPIdentifier_Lock_BreakLock_OutputArguments Variable.
        /// </summary>
        public static readonly ExpandedNodeId MyFancyAxis_CPIdentifier_Lock_BreakLock_OutputArguments = new ExpandedNodeId(MyCompany.Variables.MyFancyAxis_CPIdentifier_Lock_BreakLock_OutputArguments, MyCompany.Namespaces.MyCompany);
    }
    #endregion

    #region BrowseName Declarations
    /// <summary>
    /// Declares all of the BrowseNames used in the Model Design.
    /// </summary>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class BrowseNames
    {
        /// <summary>
        /// The BrowseName for the MyFancyAxis component.
        /// </summary>
        public const string MyFancyAxis = "MyFancyAxis";

        /// <summary>
        /// The BrowseName for the MyFancyAxisType component.
        /// </summary>
        public const string MyFancyAxisType = "MyFancyAxisType";

        /// <summary>
        /// The BrowseName for the Skills component.
        /// </summary>
        public const string Skills = "Skills";
    }
    #endregion

    #region Namespace Declarations
    /// <summary>
    /// Defines constants for all namespaces referenced by the model design.
    /// </summary>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class Namespaces
    {
        /// <summary>
        /// The URI for the MyCompany namespace (.NET code namespace is 'MyCompany').
        /// </summary>
        public const string MyCompany = "https://example.com/UA/MyCompany/";

        /// <summary>
        /// The URI for the MyCompanyXsd namespace (.NET code namespace is 'MyCompany').
        /// </summary>
        public const string MyCompanyXsd = "https://example.com/UA/MyCompany/Types.xsd";

        /// <summary>
        /// The URI for the OpcUa namespace (.NET code namespace is 'Opc.Ua').
        /// </summary>
        public const string OpcUa = "http://opcfoundation.org/UA/";

        /// <summary>
        /// The URI for the OpcUaXsd namespace (.NET code namespace is 'Opc.Ua').
        /// </summary>
        public const string OpcUaXsd = "http://opcfoundation.org/UA/2008/02/Types.xsd";

        /// <summary>
        /// The URI for the OpcUaSkills namespace (.NET code namespace is 'Opc.Ua.Skills').
        /// </summary>
        public const string OpcUaSkills = "http://opcfoundation.org/UA/Skills/";

        /// <summary>
        /// The URI for the OpcUaSkillsXsd namespace (.NET code namespace is 'Opc.Ua.Skills').
        /// </summary>
        public const string OpcUaSkillsXsd = "http://opcfoundation.org/UA/Skills/Types.xsd";

        /// <summary>
        /// The URI for the ExampleLinearAxisWithGripper namespace (.NET code namespace is 'ExampleLinearAxisWithGripper').
        /// </summary>
        public const string ExampleLinearAxisWithGripper = "https://example.com/UA/Examples/LinearAxisWithGripper/";

        /// <summary>
        /// The URI for the ExampleLinearAxisWithGripperXsd namespace (.NET code namespace is 'ExampleLinearAxisWithGripper').
        /// </summary>
        public const string ExampleLinearAxisWithGripperXsd = "https://example.com/UA/Examples/LinearAxisWithGripper/Types.xsd";

        /// <summary>
        /// The URI for the OpcUaDi namespace (.NET code namespace is 'Opc.Ua.Di').
        /// </summary>
        public const string OpcUaDi = "http://opcfoundation.org/UA/DI/";

        /// <summary>
        /// The URI for the OpcUaDiXsd namespace (.NET code namespace is 'Opc.Ua.Di').
        /// </summary>
        public const string OpcUaDiXsd = "http://opcfoundation.org/UA/DI/Types.xsd";
    }
    #endregion
}