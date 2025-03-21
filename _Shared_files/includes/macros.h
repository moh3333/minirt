/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:03:27 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/11 21:30:36 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define EPSILON			0.00001
# define SPHER				1
# define PLANE				2
# define CYLINDER			3
# define CONE				4
# define INIT				5
# define BLACK				0x0000000FF
# define BLOCK_SIZE			100000000000
# define HIGHT				1600
# define WIDTH				900
# define BAD_TEXTUR			"Invalid File Texture, Could Not Find It"
# define NO_CAM				"Camera Missed"
# define NO_AMB				"Ambiant Missed"
# define INVALID_CORD		"Invalid Cordinations In File"
# define INVALID_COLOR		"Invalid Color In File"
# define COLOR_OUT_OF_RANG	"Color RGB Out Of Range <<0.0 --- 255.0>>"
# define BIG_NUMBER			"Big Number Detected On File"
# define INDEFINED_OBJECT	"Uknown Identifier In File"
# define MALLOC_FAILS		"Malloc Syscall Fails"
# define DUPLICAT_CAM		"Camera Can Only Be Declared Once"
# define BAD_INFORM_CAM		"Camera Bad Number Of Params"
# define INVALID_FOV		"Invalid FOV: Out Of Rnage << 0.0 --- 180.0>>"
# define DUPLICAT_LIGHT		"Light Can Only Be Declared Once"
# define BAD_INFORM_LIGHT	"Light Bad Bad Number Of Params"
# define INVALID_LIGHT_N	"Invalid Light Ratio Should Be a Number"
# define INVALID_LIGHT_R	"Invalid Light Ratio Out Of Range <<0.0 --- 1.0>>"
# define BAD_INFORM_AMB		"Ambiant Bad Number Of Param"
# define DUPLICAT_AMB		"Ambiant Can Only Be Declared Once"
# define INVALID_AMB_N		"Invalid Ambiant Ratio Should Be a Number"
# define INVALID_AMB_R		"Invalid Ambiant Ratio Out Of Range <<0.0 --- 1.0>>"
# define INVALID_NORMAL		"Invalid Normal Out Of Range <<0.0 --- 1.0>>"
# define BAD_INFORM_SPH		"Spher Bad Params"
# define INVALID_SPHERE_RD	"Invalid Spher Raduis Should Be a Positive Number "
# define BAD_INFORM_PL		"Plane Bad Number Of Param"
# define BAD_INFORM_PL_CK	"Plane Checker Bad Param"
# define BAD_INFORM_SP_CK	"Spher Checker Bad Param"
# define UKNOWN				"Uknown Feature"
# define INVALID_CYL_DATA	"Cylinder Bad Number Of Param"
# define INVALID_CYL_D_H	"Cylinder Hight And Diametre Should Be  Numbers"
# define INVALID_CO_DATA	"Cone Bad Number Of Param"
# define INVALID_CO_D_H		"Cone Hight And Diametre Should Be  Numbers"
# define VALID_NAME			"Programe Require Filename.rt Extention File"
# define OPEN_FAILS			"Can't Open File"
# define BAD_PARAM_IN_FILE	"Bad Param In File"
# define DOUBLE_BUMP		"C'ant Use More Than One Bump"
# define DOUBLE_TEX			"C'ant Use More Than One Texture"

#endif