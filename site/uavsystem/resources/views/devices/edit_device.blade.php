@extends('layouts.layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.device_insert') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.device_insert') }}
@endsection

@section('content')
	@include('forms.device_form')
@endsection
