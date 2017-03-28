# Python stubs generated by omniidl from idl/MoveService.idl
# DO NOT EDIT THIS FILE!

import omniORB, _omnipy
from omniORB import CORBA, PortableServer
_0_CORBA = CORBA


_omnipy.checkVersion(4,2, __file__, 1)

try:
    property
except NameError:
    def property(*args):
        return None


#
# Start of module "_GlobalIDL"
#
__name__ = "_GlobalIDL"
_0__GlobalIDL = omniORB.openModule("_GlobalIDL", r"idl/MoveService.idl")
_0__GlobalIDL__POA = omniORB.openModule("_GlobalIDL__POA", r"idl/MoveService.idl")


# #include "BasicDataType.idl"
import BasicDataType_idl
_0_RTC = omniORB.openModule("RTC")
_0_RTC__POA = omniORB.openModule("RTC__POA")

# interface MoveService
_0__GlobalIDL._d_MoveService = (omniORB.tcInternal.tv_objref, "IDL:MoveService:1.0", "MoveService")
omniORB.typeMapping["IDL:MoveService:1.0"] = _0__GlobalIDL._d_MoveService
_0__GlobalIDL.MoveService = omniORB.newEmptyClass()
class MoveService :
    _NP_RepositoryId = _0__GlobalIDL._d_MoveService[1]

    def __init__(self, *args, **kw):
        raise RuntimeError("Cannot construct objects of this type.")

    _nil = CORBA.Object._nil


_0__GlobalIDL.MoveService = MoveService
_0__GlobalIDL._tc_MoveService = omniORB.tcInternal.createTypeCode(_0__GlobalIDL._d_MoveService)
omniORB.registerType(MoveService._NP_RepositoryId, _0__GlobalIDL._d_MoveService, _0__GlobalIDL._tc_MoveService)

# MoveService operations and attributes
MoveService._d_drive = ((omniORB.tcInternal.tv_short, omniORB.tcInternal.tv_short), (), None)

# MoveService object reference
class _objref_MoveService (CORBA.Object):
    _NP_RepositoryId = MoveService._NP_RepositoryId

    def __init__(self, obj):
        CORBA.Object.__init__(self, obj)

    def drive(self, *args):
        return self._obj.invoke("drive", _0__GlobalIDL.MoveService._d_drive, args)

omniORB.registerObjref(MoveService._NP_RepositoryId, _objref_MoveService)
_0__GlobalIDL._objref_MoveService = _objref_MoveService
del MoveService, _objref_MoveService

# MoveService skeleton
__name__ = "_GlobalIDL__POA"
class MoveService (PortableServer.Servant):
    _NP_RepositoryId = _0__GlobalIDL.MoveService._NP_RepositoryId


    _omni_op_d = {"drive": _0__GlobalIDL.MoveService._d_drive}

MoveService._omni_skeleton = MoveService
_0__GlobalIDL__POA.MoveService = MoveService
omniORB.registerSkeleton(MoveService._NP_RepositoryId, MoveService)
del MoveService
__name__ = "_GlobalIDL"

#
# End of module "_GlobalIDL"
#
__name__ = "MoveService_idl"

_exported_modules = ( "_GlobalIDL", )

# The end.
