@extends('layouts.uav_layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.uav_edit') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.uav_edit') }}
@endsection

@section('uav_box_title')
    {{ trans('adminlte_lang::message.uav_edit') }}
@endsection

@section('uav_main_content')
	@include('forms.uav_form')
@endsection

@section('network_box_title')
    {{ trans('adminlte_lang::message.uav_network interface') }}
@endsection

@section('uav_network_content')
	@include('forms.uav_net_form')
@endsection


