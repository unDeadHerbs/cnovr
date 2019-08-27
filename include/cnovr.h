// Copyright 2019 <>< Charles Lohr licensable under the MIT/X11 or NewBSD licenses.

#ifndef _CNOVR_H
#define _CNOVR_H

#include <cnovrparts.h>
#include <openvr_capi.h>
#include <stdbool.h>


//Attach an alert to a specific object (or null for the general alarm)
//1 = critical error.
//2 = serious error (missing files, etc.)
//5 = debug.
void CNOVRAlert( cnovr_model * obj, int priority, const char * format, ... );
#define ovrprintf(x...) CNOVRAlert( 0, 5, x)

//////////////////////////////////////////////////////////////////////////////

#define UNIFORMSLOT_MODEL       4
#define UNIFORMSLOT_VIEW        5
#define UNIFORMSLOT_PERSPECTIVE 6
#define UNIFORMSLOT_RENDERPROPS 7


//////////////////////////////////////////////////////////////////////////////
// Globals (State)
struct cnovrstate_t
{
	//Current rendertarget
	cnovr_rf_buffer * sterotargets[2];
	cnovr_rf_buffer * previewtarget;

	//GL State Stuff
	float iRTWidth;
	float iRTHeight;
	float fNear;
	float fFar;

	//XXX What about the view and perspective matricies?
	float mModel[16];	//Current model matrix, changes per object. (SLOT=4)
	float mView[16];	//Current view matrix, changes per eye.     (SLOT=5)
	float mPerspective[16];                                      // (SLOT=6)

	//Notes:
	// Standard CNOVR Uniforms:
	// 16 = [ Render Width, Render Height, Far, Near ]
	// 17 = Perspective
	// 18 = View
	// 19 = Model

	cnovr_model * pCurrentModel;  //Will this change to a context?
	cnovr_simple_node * pRootNode;

	struct VR_IVRSystem_FnTable * oSystem;
	struct VR_IVRRenderModels_FnTable * oRenderModels;

	cnovr_pose pPreviewPose;
	float fPreviewFOV;

	bool has_ovr;
	bool has_preview;
	short    iPreviewWidth, iPreviewHeight;
	short    iEyeRenderWidth, iEyeRenderHeight;
} __attribute__((packed));

extern struct cnovrstate_t * cnovrstate;

//////////////////////////////////////////////////////////////////////////////
int CNOVRInit( const char * appname, int screenx, int screeny, int allow_init_without_vr );
void CNOVRUpdate();
int CNOVRCheck(); //Check for errors.

void CNOVRShaderLoadedSetUniformsInternal();

#endif

