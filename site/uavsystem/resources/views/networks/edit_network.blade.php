@extends('layouts.layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.network_edit') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.network_edit') }}
@endsection

@section('content')
	@include('forms.network_form')
@endsection
