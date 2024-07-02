/* NAppGUI Huffman Compression */

#include <nappgui.h>
#include "HuffTree.h"
const string PATH = "../../text/";
typedef struct _app_t App;

struct _app_t
{
	Window* window;
	Label* encodeSuccLabel;
	Label* decodeSuccLabel;
	Edit* encodedFile;
	Edit* dataFile;
};

/*---------------------------------------------------------------------------*/

static void i_OnDecodeButton(App* app, Event* e)
{

	const char_t* fileName = edit_get_text(app->dataFile);
	label_text(app->decodeSuccLabel, fileName);

	string fileNameString = PATH;
	fileNameString.append(string(fileName)).append(".txt");

	HuffTree h;
	try
	{
		h.decodeTextToFile(fileNameString, "../../text/decoded.txt");
		label_text(app->decodeSuccLabel, "Data Decoded Successfully!");
	}
	catch (runtime_error r)
	{
		label_text(app->decodeSuccLabel, r.what());
	}
	unref(e);
}

static void i_OnEncodeButton(App* app, Event* e)
{
	const char_t* fileName = edit_get_text(app->encodedFile);
	label_text(app->encodeSuccLabel, fileName);

	string fileNameString = PATH;
	fileNameString.append(string(fileName)).append(".txt");

	HuffTree h;
	try
	{
		h.encodeTextToFile(fileNameString, "../../text/encoded.txt");
		string ratio = "Ratio: ";
		ratio.append(to_string(h.calculateRatio(fileNameString, "../../text/encoded.txt")));
		const char* str = ratio.c_str();
		label_text(app->encodeSuccLabel, str);
	}
	catch (runtime_error r)
	{
		label_text(app->encodeSuccLabel, r.what());
	}
	unref(e);
}

/*---------------------------------------------------------------------------*/

static Panel* i_panel(App* app)
{
	Panel* panel = panel_create();
	Layout* layout = layout_create(4, 2);

	Label* decodeLabel = label_create();
	Label* encodeLabel = label_create();
	Button* decodeButton = button_push();
	Button* encodeButton = button_push();
	app->dataFile = edit_create();
	app->encodedFile = edit_create();
	app->decodeSuccLabel = label_multiline();
	app->encodeSuccLabel = label_multiline();
	//Set components' text
	label_text(decodeLabel, "Data File");
	button_text(decodeButton, "Decode");
	label_text(encodeLabel, "Encoded File");
	button_text(encodeButton, "Encode");
	button_OnClick(decodeButton, listener(app, i_OnDecodeButton, App));
	button_OnClick(encodeButton, listener(app, i_OnEncodeButton, App));
	label_color(app->decodeSuccLabel, kCOLOR_RED);
	label_color(app->encodeSuccLabel, kCOLOR_RED);
	//Align Buttons and labels
	layout_halign(layout, 1, 1, ekLEFT);
	layout_halign(layout, 0, 1, ekLEFT);
	layout_halign(layout, 0, 0, ekCENTER);
	layout_halign(layout, 2, 1, ekLEFT);
	layout_halign(layout, 1, 1, ekJUSTIFY);
	layout_halign(layout, 3, 1, ekJUSTIFY);
	layout_valign(layout, 1, 1, ekJUSTIFY);
	layout_valign(layout, 3, 1, ekJUSTIFY);
	layout_valign(layout, 1, 0, ekBOTTOM);
	layout_valign(layout, 3, 0, ekBOTTOM);
	//Add components to layout
	layout_label(layout, decodeLabel, 0, 0);
	layout_button(layout, decodeButton, 2, 1);
	layout_label(layout, encodeLabel, 2, 0);
	layout_button(layout, encodeButton, 0, 1);
	layout_edit(layout, app->dataFile, 3, 0);
	layout_edit(layout, app->encodedFile, 1, 0);
	layout_label(layout, app->decodeSuccLabel, 3, 1);
	layout_label(layout, app->encodeSuccLabel, 1, 1);
	//Adjust components' size
	layout_hsize(layout, 0, 100);
	layout_vsize(layout, 0, 23);
	layout_vsize(layout, 1, 30);
	//Adjust margins
	layout_margin(layout, 20);
	layout_hmargin(layout, 1, 100);
	layout_hmargin(layout, 2, 15);
	layout_hmargin(layout, 0, 10);
	layout_vmargin(layout, 0, 15);
	layout_vmargin(layout, 1, 15);
	panel_layout(panel, layout);
	return panel;
}

/*---------------------------------------------------------------------------*/

static void i_OnClose(App* app, Event* e)
{
	osapp_finish();
	unref(app);
	unref(e);
}

/*---------------------------------------------------------------------------*/

static App* i_create(void)
{
	App* app = heap_new0(App);
	Panel* panel = i_panel(app);
	app->window = window_create(ekWINDOW_STD);
	window_panel(app->window, panel);
	window_title(app->window, "Huffman Compression");
	window_origin(app->window, v2df(250, 200));
	window_OnClose(app->window, listener(app, i_OnClose, App));
	window_show(app->window);
	return app;
}

/*---------------------------------------------------------------------------*/

static void i_destroy(App** app)
{
	window_destroy(&(*app)->window);
	heap_delete(app, App);
}

/*---------------------------------------------------------------------------*/

#include "osmain.h"
osmain(i_create, i_destroy, "", App)
