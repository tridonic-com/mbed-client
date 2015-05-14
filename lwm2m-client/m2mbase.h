/*
 * Copyright (c) 2015 ARM. All rights reserved.
 */
#ifndef M2M_BASE_H
#define M2M_BASE_H

// Support for std args
#include <stdint.h>
#include "lwm2m-client/m2mconfig.h"
#include "lwm2m-client/m2mreportobserver.h"

//FORWARD DECLARATION
class M2MObservationHandler;
class M2MReportHandler;

/**
 *  @brief M2MBase.
 *  This class is the base class based on which all LWM2M object model
 *  can be created. This serves base class for both Object as well as Resources.
 */

class M2MBase : public M2MReportObserver {

public:

    /**
      * Enum to define the type of object
      */
    typedef enum {
        Object = 0x0,
        Resource = 0x1,
        ObjectInstance = 0x2
    } BaseType;

    /**
     * @brief Enum defining operation which can be
     * supported by a given resource.
    */
    typedef enum {
        Static,
        Dynamic,
        Directory
    }Mode;

    /**
     * Enum defining operation which can be
     * supported by a given resource.
    */
    typedef enum {
        NOT_ALLOWED           = 0x00,
        GET_ALLOWED           = 0x01,
        PUT_ALLOWED           = 0x02,
        GET_PUT_ALLOWED       = 0x03,
        POST_ALLOWED          = 0x04,
        GET_POST_ALLOWED      = 0x05,
        PUT_POST_ALLOWED      = 0x06,
        GET_PUT_POST_ALLOWED  = 0x07,
        DELETE_ALLOWED        = 0x08
    }Operation;

protected:

    // Prevents the use of default constructor.
    M2MBase();

    // Prevents the use of assignment operator.
    M2MBase& operator=( const M2MBase& /*other*/ );

    // Prevents the use of copy constructor
    M2MBase( const M2MBase& /*other*/ );

    /**
     * @brief Constructor
     * @param baseType, Type of object created
     * @param name, name of the object
     * @param id, ID of the object
     */
    M2MBase(const String &name,
            M2MBase::Mode mode);
public:

    /**
     * Destructor
     */
    virtual ~M2MBase();

    /**
     * @brief Sets the operation type for object.
     * @param operation, Operation to be set
     */
    virtual void set_operation(M2MBase::Operation operation);

    /**
     * @brief Sets the interface description of the object.
     * @param description, Description to be set.
     */
    virtual void set_interface_description(const String &description);

    /**
     * @brief Sets the resource type of the object.
     * @param description, Description to be set.
     */
    virtual void set_resource_type(const String &resource_type);

    /**
     * @brief Sets the coap content type of the object.
     * @param content_type, Content Type to be set based on
     * CoAP specifications.
     */
    virtual void set_coap_content_type(const uint8_t content_type);

    /**
     * @brief Sets the observable mode for the object.
     * @param Value for the observation.
     */
    virtual void set_observable(bool observable);

    /**
     * @brief Sets that object is under observation.
     * @param Value for the observation.
     * @param handler, Handler object for sending
     * observation callbacks.
     */
    virtual void set_under_observation(bool observed,
                                       M2MObservationHandler *handler);

    /**
     * @brief Sets observation token value.
     * @param token, Pointer to the token of the resource.
     * @param length , Length of the token pointer.
     */
    virtual void set_observation_token(const uint8_t *token,
                                       const uint8_t length);

    /**
     * Sets instance ID of the object
     * @param Instance ID of the object
     */
    virtual void set_instance_id(const uint16_t instance_id);

    /**
     * @brief Sets the value of the given resource.
     * @param value, Pointer to the value to be set on the resource.
     * @param value_length , Length of the value pointer.
     * @param is_numeric , Defines whether the value is numeric or string format.
     * Default is false which means value is in string format.
     * @return True if successfully set else false.
     */
    virtual bool set_value(const uint8_t *value, const uint32_t value_length, bool is_numeric = false);

    /**
     * Sets Observation number of the object
     * @param observation_number of the object.
     */
    virtual void set_observation_number(const uint16_t observation_number);

    /**
     * @brief Returns object type
     * @return BaseType
     */
    virtual M2MBase::BaseType base_type() const;

    /**
     * @brief Returns the operation type of the object
     * @return Operation, Supported operation on the object
     */
    virtual M2MBase::Operation operation() const;

    /**
     * @brief Returns object name
     * @return Name for the object
     */
    virtual const String &name() const;

    /**
     * @brief Returns object's Instance ID
     * @returns Instance ID of the object
     */
    virtual uint16_t instance_id() const;

    /**
     * @brief Returns interface description of the object.
     * @return Description of the object.
     */
    virtual const String& interface_description() const;

    /**
     * @brief Returns resource type of the object.
     * @return Resource Type of the object.
     */
    virtual const String& resource_type() const;

    /**
     * @brief Returns coap content type of the object.
     * @param content_type, .
     * @return Content Type of the object.
     */
    virtual uint8_t coap_content_type() const;

    /**
     * @brief Returns the observation status of the object
     * @return True if observable else false
     */
    virtual bool is_observable() const;

    /**
     * @brief Returns the observation token of the object
     * @param value[OUT], pointer to the value of token.
     * @param value_length[OUT], length to the token pointer.
     */
    virtual void get_observation_token(uint8_t *&token, uint32_t &token_length);

    /**
     * @brief Returns the mode of the resource
     * @return Mode of the resource.
     */
     virtual Mode mode() const;

    /**
     * @brief Returns the value of the given resource.
     * @param value[OUT], pointer to the value of resource.
     * @param value_length[OUT], length to the value pointer.
     */
    virtual void get_value(uint8_t *&value, uint32_t &value_length);

    /**
     * @brief Returns the observation number.
     * @return observation number for the object
     */
    virtual uint16_t observation_number() const;

    /**
     * @brief Parses the received query for notification
     * attribute.
     * @return true if required attributes are present else false.
     */
    virtual bool handle_observation_attribute(char *&query);

protected : // from M2MReportObserver

    virtual void observation_to_be_sent();

protected:

    /**
     * @brief Sets the Base type for object.
     * @param type, Type of the base object
     */
    virtual void set_base_type(M2MBase::BaseType type);

    /**
     * @brief Removes resource from coap structure.
     * @param resource_name, Name of the resource.
     */
    virtual void remove_resource_from_coap(const String &resource_name);

    /**
     * @brief Removes object from NSDL list.
     */
    virtual void remove_object_from_coap();

private:

    M2MReportHandler           *_report_handler;
    M2MObservationHandler      *_observation_handler;
    M2MBase::Operation          _operation;
    M2MBase::Mode               _mode;
    M2MBase::BaseType           _base_type;
    String                      _name;
    String                      _resource_type;
    String                      _interface_description;
    uint8_t                     _coap_content_type;
    uint16_t                    _instance_id;
    bool                        _observable;
    uint16_t                    _observation_number;
    uint8_t                     *_value;
    uint32_t                    _value_length;
    bool                        _is_numeric;
    uint8_t                     *_token;
    uint8_t                     _token_length;

friend class Test_M2MBase;

};

#endif // M2M_BASE_H
