/*
 * Copyright 2017 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// This file has been auto-generated by bindings/code_generator_cobalt.py. DO NOT MODIFY!
// Auto-generated from template: bindings/mozjs-45/templates/interface.cc.template

// clang-format off

#include "MozjsEnumerationInterface.h"

#include "base/debug/trace_event.h"
#include "cobalt/base/polymorphic_downcast.h"
#include "cobalt/script/global_environment.h"
#include "cobalt/script/opaque_handle.h"
#include "cobalt/script/script_object.h"

#include "base/lazy_instance.h"
#include "cobalt/script/mozjs-45/callback_function_conversion.h"
#include "cobalt/script/exception_state.h"
#include "cobalt/script/mozjs-45/conversion_helpers.h"
#include "cobalt/script/mozjs-45/mozjs_exception_state.h"
#include "cobalt/script/mozjs-45/mozjs_callback_function.h"
#include "cobalt/script/mozjs-45/mozjs_global_environment.h"
#include "cobalt/script/mozjs-45/mozjs_object_handle.h"
#include "cobalt/script/mozjs-45/mozjs_property_enumerator.h"
#include "cobalt/script/mozjs-45/mozjs_user_object_holder.h"
#include "cobalt/script/mozjs-45/proxy_handler.h"
#include "cobalt/script/mozjs-45/type_traits.h"
#include "cobalt/script/mozjs-45/wrapper_factory.h"
#include "cobalt/script/mozjs-45/wrapper_private.h"
#include "cobalt/script/property_enumerator.h"
#include "third_party/mozjs-45/js/src/jsapi.h"
#include "third_party/mozjs-45/js/src/jsfriendapi.h"

namespace {
using cobalt::bindings::testing::EnumerationInterface;
using cobalt::bindings::testing::MozjsEnumerationInterface;
using cobalt::script::CallbackInterfaceTraits;
using cobalt::script::GlobalEnvironment;
using cobalt::script::OpaqueHandle;
using cobalt::script::OpaqueHandleHolder;
using cobalt::script::ScriptObject;
using cobalt::script::Wrappable;

using cobalt::script::CallbackFunction;
using cobalt::script::CallbackInterfaceTraits;
using cobalt::script::ExceptionState;
using cobalt::script::mozjs::FromJSValue;
using cobalt::script::mozjs::kConversionFlagNullable;
using cobalt::script::mozjs::kConversionFlagRestricted;
using cobalt::script::mozjs::kConversionFlagTreatNullAsEmptyString;
using cobalt::script::mozjs::kConversionFlagTreatUndefinedAsEmptyString;
using cobalt::script::mozjs::kNoConversionFlags;
using cobalt::script::mozjs::InterfaceData;
using cobalt::script::mozjs::MozjsCallbackFunction;
using cobalt::script::mozjs::MozjsExceptionState;
using cobalt::script::mozjs::MozjsGlobalEnvironment;
using cobalt::script::mozjs::MozjsUserObjectHolder;
using cobalt::script::mozjs::MozjsPropertyEnumerator;
using cobalt::script::mozjs::ProxyHandler;
using cobalt::script::mozjs::ToJSValue;
using cobalt::script::mozjs::TypeTraits;
using cobalt::script::mozjs::WrapperPrivate;
using cobalt::script::mozjs::WrapperFactory;
using cobalt::script::Wrappable;
// Declare and define these in the same namespace that the other overloads
// were brought into with the using declaration.
void ToJSValue(
    JSContext* context,
    EnumerationInterface::TestEnum in_enum,
    JS::MutableHandleValue out_value);
void FromJSValue(JSContext* context, JS::HandleValue value,
                 int conversion_flags, ExceptionState* exception_state,
                 EnumerationInterface::TestEnum* out_enum);
}  // namespace

namespace cobalt {
namespace bindings {
namespace testing {

namespace {

class MozjsEnumerationInterfaceHandler : public ProxyHandler {
 public:
  MozjsEnumerationInterfaceHandler()
      : ProxyHandler(indexed_property_hooks, named_property_hooks) {}

 private:
  static NamedPropertyHooks named_property_hooks;
  static IndexedPropertyHooks indexed_property_hooks;
};

ProxyHandler::NamedPropertyHooks
MozjsEnumerationInterfaceHandler::named_property_hooks = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};
ProxyHandler::IndexedPropertyHooks
MozjsEnumerationInterfaceHandler::indexed_property_hooks = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

static base::LazyInstance<MozjsEnumerationInterfaceHandler>
    proxy_handler;

bool Constructor(JSContext* context, unsigned int argc, JS::Value* vp);
bool HasInstance(JSContext *context, JS::HandleObject type,
                   JS::MutableHandleValue vp, bool *success) {
  JS::RootedObject global_object(
      context, JS_GetGlobalForObject(context, type));
  DCHECK(global_object);

  JS::RootedObject prototype(
      context, MozjsEnumerationInterface::GetPrototype(context, global_object));

  // |IsDelegate| walks the prototype chain of an object returning true if
  // .prototype is found.
  bool is_delegate;
  if (!IsDelegate(context, prototype, vp, &is_delegate)) {
    *success = false;
    return false;
  }

  *success = is_delegate;
  return true;
}

const JSClass instance_class_definition = {
    "EnumerationInterface",
    0 | JSCLASS_HAS_PRIVATE,
    NULL,  // addProperty
    NULL,  // delProperty
    NULL,  // getProperty
    NULL,  // setProperty
    NULL,  // enumerate
    NULL,  // resolve
    NULL,  // mayResolve
    &WrapperPrivate::Finalizer,  // finalize
    NULL,  // call
    NULL,  // hasInstance
    NULL,  // construct
    &WrapperPrivate::Trace,  // trace
};

const JSClass prototype_class_definition = {
    "EnumerationInterfacePrototype",
};

const JSClass interface_object_class_definition = {
    "EnumerationInterfaceConstructor",
    0,
    NULL,  // addProperty
    NULL,  // delProperty
    NULL,  // getProperty
    NULL,  // setProperty
    NULL,  // enumerate
    NULL,  // resolve
    NULL,  // mayResolve
    NULL,  // finalize
    NULL,  // call
    &HasInstance,
    Constructor,
};

bool get_enumProperty(
    JSContext* context, unsigned argc, JS::Value* vp) {
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  JS::RootedObject object(context, &args.thisv().toObject());
  MozjsGlobalEnvironment* global_environment =
      static_cast<MozjsGlobalEnvironment*>(JS_GetContextPrivate(context));
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<EnumerationInterface>())) {
    MozjsExceptionState exception(context);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return false;
  }
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromObject(context, object);
  EnumerationInterface* impl =
      wrapper_private->wrappable<EnumerationInterface>().get();

  if (!exception_state.is_exception_set()) {
    ToJSValue(context,
              impl->enum_property(),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    args.rval().set(result_value);
  }
  return !exception_state.is_exception_set();
}

bool set_enumProperty(
    JSContext* context, unsigned argc, JS::Value* vp) {

  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  JS::RootedObject object(context, &args.thisv().toObject());

  MozjsGlobalEnvironment* global_environment =
      static_cast<MozjsGlobalEnvironment*>(JS_GetContextPrivate(context));
  WrapperFactory* wrapper_factory = global_environment->wrapper_factory();
  if (!wrapper_factory->DoesObjectImplementInterface(
        object, base::GetTypeId<EnumerationInterface>())) {
    MozjsExceptionState exception(context);
    exception.SetSimpleException(script::kDoesNotImplementInterface);
    return false;
  }
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromObject(context, object);
  EnumerationInterface* impl =
      wrapper_private->wrappable<EnumerationInterface>().get();
  TypeTraits<EnumerationInterface::TestEnum >::ConversionType value;
  if (args.length() != 1) {
    NOTREACHED();
    return false;
  }
  FromJSValue(context, args[0], kNoConversionFlags, &exception_state,
              &value);
  if (exception_state.is_exception_set()) {
    return false;
  }

  impl->set_enum_property(value);
  result_value.set(JS::UndefinedHandleValue);
  return !exception_state.is_exception_set();
}



const JSPropertySpec prototype_properties[] = {
  {  // Read/Write property
    "enumProperty",
    JSPROP_SHARED | JSPROP_ENUMERATE,
    { { &get_enumProperty, NULL } },
    { { &set_enumProperty, NULL } },
  },
  JS_PS_END
};

const JSFunctionSpec prototype_functions[] = {
  JS_FS_END
};

const JSPropertySpec interface_object_properties[] = {
  JS_PS_END
};

const JSFunctionSpec interface_object_functions[] = {
  JS_FS_END
};

const JSPropertySpec own_properties[] = {
  JS_PS_END
};

void InitializePrototypeAndInterfaceObject(
    InterfaceData* interface_data, JSContext* context,
    JS::HandleObject global_object) {
  DCHECK(!interface_data->prototype);
  DCHECK(!interface_data->interface_object);
  DCHECK(JS_IsGlobalObject(global_object));

  JS::RootedObject parent_prototype(
      context, JS_GetObjectPrototype(context, global_object));
  DCHECK(parent_prototype);

  interface_data->prototype = JS_NewObjectWithGivenProto(
    context, &prototype_class_definition, parent_prototype
  );

  JS::RootedObject rooted_prototype(context, interface_data->prototype);
  bool success = JS_DefineProperties(
      context,
      rooted_prototype,
      prototype_properties);

  DCHECK(success);
  success = JS_DefineFunctions(
      context, rooted_prototype, prototype_functions);
  DCHECK(success);

  JS::RootedObject function_prototype(
      context, JS_GetFunctionPrototype(context, global_object));
  DCHECK(function_prototype);
  // Create the Interface object.
  interface_data->interface_object = JS_NewObjectWithGivenProto(
      context, &interface_object_class_definition,
      function_prototype);

  // Add the InterfaceObject.name property.
  JS::RootedObject rooted_interface_object(
      context, interface_data->interface_object);
  JS::RootedValue name_value(context);
  const char name[] =
      "EnumerationInterface";
  name_value.setString(JS_NewStringCopyZ(context, name));
  success = JS_DefineProperty(
      context, rooted_interface_object, "name", name_value, JSPROP_READONLY,
      NULL, NULL);
  DCHECK(success);

  // Add the InterfaceObject.length property. It is set to the length of the
  // shortest argument list of all overload constructors.
  JS::RootedValue length_value(context);
  length_value.setInt32(0);
  success = JS_DefineProperty(
      context, rooted_interface_object, "length", length_value,
      JSPROP_READONLY, NULL, NULL);
  DCHECK(success);

  // Define interface object properties (including constants).
  success = JS_DefineProperties(context, rooted_interface_object,
                                interface_object_properties);
  DCHECK(success);
  // Define interface object functions (static).
  success = JS_DefineFunctions(context, rooted_interface_object,
                               interface_object_functions);
  DCHECK(success);

  // Set the Prototype.constructor and Constructor.prototype properties.
  DCHECK(interface_data->interface_object);
  DCHECK(interface_data->prototype);
  success = JS_LinkConstructorAndPrototype(
      context,
      rooted_interface_object,
      rooted_prototype);
  DCHECK(success);
}

InterfaceData* GetInterfaceData(JSContext* context) {
  MozjsGlobalEnvironment* global_environment =
      static_cast<MozjsGlobalEnvironment*>(JS_GetContextPrivate(context));
  // Use the address of the properties definition for this interface as a
  // unique key for looking up the InterfaceData for this interface.
  intptr_t key = reinterpret_cast<intptr_t>(&own_properties);
  InterfaceData* interface_data = global_environment->GetInterfaceData(key);
  if (!interface_data) {
    interface_data = new InterfaceData();
    DCHECK(interface_data);
    global_environment->CacheInterfaceData(key, interface_data);
    DCHECK_EQ(interface_data, global_environment->GetInterfaceData(key));
  }
  return interface_data;
}

}  // namespace

// static
JSObject* MozjsEnumerationInterface::CreateProxy(
    JSContext* context, const scoped_refptr<Wrappable>& wrappable) {
  DCHECK(MozjsGlobalEnvironment::GetFromContext(context));
  JS::RootedObject global_object(
      context,
      MozjsGlobalEnvironment::GetFromContext(context)->global_object());
  DCHECK(global_object);

  InterfaceData* interface_data = GetInterfaceData(context);
  JS::RootedObject prototype(context, GetPrototype(context, global_object));
  DCHECK(prototype);
  JS::RootedObject new_object(
      context,
      JS_NewObjectWithGivenProto(
          context, &instance_class_definition, prototype));
  DCHECK(new_object);
  JS::RootedObject proxy(context,
      ProxyHandler::NewProxy(
          context, proxy_handler.Pointer(), new_object, prototype));
  WrapperPrivate::AddPrivateData(context, proxy, wrappable);
  return proxy;
}

// static
const JSClass* MozjsEnumerationInterface::PrototypeClass(
      JSContext* context) {
  DCHECK(MozjsGlobalEnvironment::GetFromContext(context));
  JS::RootedObject global_object(
      context,
      MozjsGlobalEnvironment::GetFromContext(context)->global_object());
  DCHECK(global_object);

  JS::RootedObject prototype(context, GetPrototype(context, global_object));
  const JSClass* proto_class = JS_GetClass(prototype);
  return proto_class;
}

// static
JSObject* MozjsEnumerationInterface::GetPrototype(
    JSContext* context, JS::HandleObject global_object) {
  DCHECK(JS_IsGlobalObject(global_object));

  InterfaceData* interface_data = GetInterfaceData(context);
  if (!interface_data->prototype) {
    // Create new prototype that has all the props and methods
    InitializePrototypeAndInterfaceObject(
        interface_data, context, global_object);
  }
  DCHECK(interface_data->prototype);
  return interface_data->prototype;
}

// static
JSObject* MozjsEnumerationInterface::GetInterfaceObject(
    JSContext* context, JS::HandleObject global_object) {
  DCHECK(JS_IsGlobalObject(global_object));

  InterfaceData* interface_data = GetInterfaceData(context);
  if (!interface_data->interface_object) {
    InitializePrototypeAndInterfaceObject(
        interface_data, context, global_object);
  }
  DCHECK(interface_data->interface_object);
  return interface_data->interface_object;
}


namespace {
bool Constructor(JSContext* context, unsigned int argc, JS::Value* vp) {
  MozjsExceptionState exception_state(context);
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

  scoped_refptr<EnumerationInterface> new_object =
      new EnumerationInterface();
  JS::RootedValue result_value(context);
  ToJSValue(context, new_object, &result_value);
  DCHECK(result_value.isObject());
  args.rval().setObject(result_value.toObject());
  return true;
}
}  // namespace


}  // namespace testing
}  // namespace bindings
}  // namespace cobalt

namespace {

inline void ToJSValue(
    JSContext* context,
    EnumerationInterface::TestEnum in_enum,
    JS::MutableHandleValue out_value) {

  switch (in_enum) {
    case EnumerationInterface::kAlpha:
      ToJSValue(context, std::string("alpha"), out_value);
      return;
    case EnumerationInterface::kBeta:
      ToJSValue(context, std::string("beta"), out_value);
      return;
    case EnumerationInterface::kGamma:
      ToJSValue(context, std::string("gamma"), out_value);
      return;
    default:
      NOTREACHED();
      out_value.set(JS::UndefinedValue());
  }
}

inline void FromJSValue(JSContext* context, JS::HandleValue value,
                 int conversion_flags, ExceptionState* exception_state,
                 EnumerationInterface::TestEnum* out_enum) {
  DCHECK_EQ(0, conversion_flags) << "Unexpected conversion flags.";
  // JSValue -> IDL enum algorithm described here:
  // http://heycam.github.io/webidl/#es-enumeration
  // 1. Let S be the result of calling ToString(V).
  JS::RootedString rooted_string(context, JS::ToString(context, value));

  bool match = false;
// 3. Return the enumeration value of type E that is equal to S.
if (JS_StringEqualsAscii(
      context, rooted_string, "alpha", &match)
      && match) {
    *out_enum = EnumerationInterface::kAlpha;
  } else if (JS_StringEqualsAscii(
      context, rooted_string, "beta", &match)
      && match) {
    *out_enum = EnumerationInterface::kBeta;
  } else if (JS_StringEqualsAscii(
      context, rooted_string, "gamma", &match)
      && match) {
    *out_enum = EnumerationInterface::kGamma;
  } else {
    // 2. If S is not one of E's enumeration values, then throw a TypeError.
    exception_state->SetSimpleException(cobalt::script::kConvertToEnumFailed);
    return;
  }
}
}  // namespace
