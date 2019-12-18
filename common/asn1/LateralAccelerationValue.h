/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "its_facilities_pdu_all.asn"
 * 	`asn1c -fnative-types -gen-PER`
 */

#ifndef	_LateralAccelerationValue_H_
#define	_LateralAccelerationValue_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum LateralAccelerationValue {
	LateralAccelerationValue_pointOneMeterPerSecSquaredToRight	= -1,
	LateralAccelerationValue_pointOneMeterPerSecSquaredToLeft	= 1,
	LateralAccelerationValue_unavailable	= 161
} e_LateralAccelerationValue;

/* LateralAccelerationValue */
typedef long	 LateralAccelerationValue_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LateralAccelerationValue;
asn_struct_free_f LateralAccelerationValue_free;
asn_struct_print_f LateralAccelerationValue_print;
asn_constr_check_f LateralAccelerationValue_constraint;
ber_type_decoder_f LateralAccelerationValue_decode_ber;
der_type_encoder_f LateralAccelerationValue_encode_der;
xer_type_decoder_f LateralAccelerationValue_decode_xer;
xer_type_encoder_f LateralAccelerationValue_encode_xer;
per_type_decoder_f LateralAccelerationValue_decode_uper;
per_type_encoder_f LateralAccelerationValue_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _LateralAccelerationValue_H_ */
#include <asn_internal.h>
