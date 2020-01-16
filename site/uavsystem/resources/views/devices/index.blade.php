@extends('layouts.layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.device') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.device') }}
@endsection

@section('content')
    @include('devices.device_table')
@endsection
