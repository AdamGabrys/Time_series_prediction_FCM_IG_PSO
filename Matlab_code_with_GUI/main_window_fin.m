function varargout = main_window_fin(varargin)
% MAIN_WINDOW_FIN MATLAB code for main_window_fin.fig
%      MAIN_WINDOW_FIN, by itself, creates a new MAIN_WINDOW_FIN or raises the existing
%      singleton*.
%
%      H = MAIN_WINDOW_FIN returns the handle to a new MAIN_WINDOW_FIN or the handle to
%      the existing singleton*.
%
%      MAIN_WINDOW_FIN('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MAIN_WINDOW_FIN.M with the given input arguments.
%
%      MAIN_WINDOW_FIN('Property','Value',...) creates a new MAIN_WINDOW_FIN or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before main_window_fin_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to main_window_fin_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help main_window_fin

% Last Modified by GUIDE v2.5 10-Feb-2016 21:56:42

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @main_window_fin_OpeningFcn, ...
                   'gui_OutputFcn',  @main_window_fin_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before main_window_fin is made visible.
function main_window_fin_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to main_window_fin (see VARARGIN)

% Choose default command line output for main_window_fin
handles.output = hObject;
handles.flag1=false;
handles.flag2=false;
% Update handles structure
guidata(hObject, handles);
set(handles.pushbutton8,'enable','off')

% UIWAIT makes main_window_fin wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = main_window_fin_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[FileName,PathName,FilterIndex] = uigetfile('*.csv');
handles.dataFileName=strcat(PathName, FileName);
handles.flag1=true;
guidata(hObject,handles)
if(handles.flag1&&handles.flag2)
    set(handles.pushbutton8,'enable','on')
end
% --- Executes on button press in pushbutton6.
function pushbutton6_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
generate_window_ffin;

% --- Executes on button press in pushbutton7.
function pushbutton7_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[FileName,PathName,FilterIndex] = uigetfile('*.csv');
handles.mapFileName=strcat(PathName, FileName)
handles.flag2=true;
guidata(hObject,handles)
if(handles.flag1&&handles.flag2)
    set(handles.pushbutton8,'enable','on')
end

% --- Executes on button press in pushbutton8.
function pushbutton8_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
Array=csvread(handles.dataFileName);
col1 = Array(:, 1);
col2 = Array(:, 2);
data=col2;
plot(col1, col2)
hold on;
[mapa,prototypes,w0,sig]=import_map(handles.mapFileName);
predictions=predict(data,mapa,prototypes,w0,sig);
t=size(predictions);
t_t=round(0.8*t);
predictions_t=predictions(1:t_t);
predictions_l=predictions(t_t+1:t);
col1_t=col1(1:t_t);
col1_l=col1(t_t+1:t);
plot(col1_t,predictions_t,'r-');
plot(col1_l,predictions_l,'g-');
legend('oryginalne dane','dane przewidywane ze zbioru treningowego','dane przewidywane ze zbioru testowego','Location','northoutside')
xlabel({'czas','format Unixowy'},'FontWeight','bold')
ylabel('wartosc [$]','FontWeight','bold')
hold off;
