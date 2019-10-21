@extends('layouts.layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.uav_edit') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.uav_edit') }}
@endsection

@section('content')
	@include('forms.uav_form')
@endsection
