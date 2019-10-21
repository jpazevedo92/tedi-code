@extends('layouts.layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.uav_insert') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.uav_insert') }}
@endsection

@section('content')
	@include('forms.uav_form')
@endsection