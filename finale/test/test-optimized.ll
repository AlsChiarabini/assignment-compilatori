; ModuleID = 'test-optimized.bc'
source_filename = "test.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx15.0.0"

@.str = private unnamed_addr constant [18 x i8] c"Test passo 1: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [18 x i8] c"Test passo 2: %d\0A\00", align 1
@.str.2 = private unnamed_addr constant [18 x i8] c"Test passo 3: %d\0A\00", align 1
@.str.3 = private unnamed_addr constant [20 x i8] c"Test combinato: %d\0A\00", align 1
@.str.4 = private unnamed_addr constant [20 x i8] c"Test complesso: %d\0A\00", align 1

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z11test_passo1ii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = add nsw i32 %0, %1
  %4 = add nsw i32 %3, %0
  %5 = add nsw i32 %4, %0
  %6 = add nsw i32 %5, %1
  %7 = add nsw i32 %6, %0
  ret i32 %7
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z11test_passo2i(i32 noundef %0) #0 {
  %2 = mul nsw i32 %0, 16
  %3 = mul nsw i32 %0, 15
  %4 = mul nsw i32 %0, 17
  %5 = sdiv i32 %0, 8
  %6 = mul nsw i32 %0, -16
  %7 = sdiv i32 %0, -8
  %8 = add nsw i32 %2, %3
  %9 = add nsw i32 %8, %4
  %10 = add nsw i32 %9, %5
  %11 = add nsw i32 %10, %6
  %12 = add nsw i32 %11, %7
  ret i32 %12
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z11test_passo3i(i32 noundef %0) #0 {
  %2 = add nsw i32 %0, 5
  %3 = sub nsw i32 %2, 5
  %4 = sub nsw i32 %0, 7
  %5 = add nsw i32 %4, 7
  %6 = mul nsw i32 %0, 3
  %7 = sdiv i32 %6, 3
  %8 = sdiv i32 %0, 4
  %9 = mul nsw i32 %8, 4
  %10 = sdiv i32 15, 3
  %11 = add nsw i32 %3, %5
  %12 = add nsw i32 %11, %7
  %13 = add nsw i32 %12, %9
  %14 = add nsw i32 %13, %10
  ret i32 %14
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z13test_combinedii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = mul nsw i32 %0, 16
  %4 = mul nsw i32 %0, 8
  %5 = sdiv i32 %4, 8
  %6 = add nsw i32 %0, 10
  %7 = sub nsw i32 %6, 10
  %8 = mul nsw i32 %0, 16
  %9 = sdiv i32 %8, 2
  %10 = mul nsw i32 %9, 2
  %11 = mul nsw i32 %1, 4
  %12 = sdiv i32 %11, 4
  %13 = add nsw i32 %3, %5
  %14 = add nsw i32 %13, %7
  %15 = add nsw i32 %14, %10
  %16 = add nsw i32 %15, %12
  ret i32 %16
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z16complex_functioniii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = alloca [50 x i32], align 16
  %5 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 0
  store i32 %0, ptr %5, align 16
  %6 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 1
  store i32 %1, ptr %6, align 4
  %7 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 2
  store i32 %2, ptr %7, align 8
  %8 = mul nsw i32 %0, 8
  %9 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 3
  store i32 %8, ptr %9, align 4
  %10 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 3
  %11 = load i32, ptr %10, align 4
  %12 = sdiv i32 %11, 8
  %13 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 4
  store i32 %12, ptr %13, align 16
  %14 = add nsw i32 %1, 5
  %15 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 5
  store i32 %14, ptr %15, align 4
  %16 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 5
  %17 = load i32, ptr %16, align 4
  %18 = sub nsw i32 %17, 5
  %19 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 6
  store i32 %18, ptr %19, align 8
  %20 = mul nsw i32 %2, 16
  %21 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 7
  store i32 %20, ptr %21, align 4
  %22 = mul nsw i32 %0, 15
  %23 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 8
  store i32 %22, ptr %23, align 16
  %24 = sdiv i32 %1, 4
  %25 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 9
  store i32 %24, ptr %25, align 4
  br label %26

26:                                               ; preds = %81, %3
  %.02 = phi i32 [ 10, %3 ], [ %82, %81 ]
  %27 = icmp slt i32 %.02, 50
  br i1 %27, label %28, label %83

28:                                               ; preds = %26
  %29 = srem i32 %.02, 5
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %31, label %38

31:                                               ; preds = %28
  %32 = sub nsw i32 %.02, 10
  %33 = sext i32 %32 to i64
  %34 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %33
  %35 = load i32, ptr %34, align 4
  %36 = sext i32 %.02 to i64
  %37 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %36
  store i32 %35, ptr %37, align 4
  br label %80

38:                                               ; preds = %28
  %39 = srem i32 %.02, 5
  %40 = icmp eq i32 %39, 1
  br i1 %40, label %41, label %48

41:                                               ; preds = %38
  %42 = sub nsw i32 %.02, 5
  %43 = sext i32 %42 to i64
  %44 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %43
  %45 = load i32, ptr %44, align 4
  %46 = sext i32 %.02 to i64
  %47 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %46
  store i32 %45, ptr %47, align 4
  br label %79

48:                                               ; preds = %38
  %49 = srem i32 %.02, 5
  %50 = icmp eq i32 %49, 2
  br i1 %50, label %51, label %59

51:                                               ; preds = %48
  %52 = sub nsw i32 %.02, 2
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %53
  %55 = load i32, ptr %54, align 4
  %56 = mul nsw i32 %55, 8
  %57 = sext i32 %.02 to i64
  %58 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %57
  store i32 %56, ptr %58, align 4
  br label %78

59:                                               ; preds = %48
  %60 = srem i32 %.02, 5
  %61 = icmp eq i32 %60, 3
  br i1 %61, label %62, label %70

62:                                               ; preds = %59
  %63 = sub nsw i32 %.02, 1
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %64
  %66 = load i32, ptr %65, align 4
  %67 = sdiv i32 %66, 8
  %68 = sext i32 %.02 to i64
  %69 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %68
  store i32 %67, ptr %69, align 4
  br label %77

70:                                               ; preds = %59
  %71 = sub nsw i32 %.02, 4
  %72 = sext i32 %71 to i64
  %73 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %72
  %74 = load i32, ptr %73, align 4
  %75 = sext i32 %.02 to i64
  %76 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %75
  store i32 %74, ptr %76, align 4
  br label %77

77:                                               ; preds = %70, %62
  br label %78

78:                                               ; preds = %77, %51
  br label %79

79:                                               ; preds = %78, %41
  br label %80

80:                                               ; preds = %79, %31
  br label %81

81:                                               ; preds = %80
  %82 = add nsw i32 %.02, 1
  br label %26, !llvm.loop !6

83:                                               ; preds = %26
  br label %84

84:                                               ; preds = %91, %83
  %.01 = phi i32 [ 0, %83 ], [ %90, %91 ]
  %.0 = phi i32 [ 0, %83 ], [ %92, %91 ]
  %85 = icmp slt i32 %.0, 50
  br i1 %85, label %86, label %93

86:                                               ; preds = %84
  %87 = sext i32 %.0 to i64
  %88 = getelementptr inbounds [50 x i32], ptr %4, i64 0, i64 %87
  %89 = load i32, ptr %88, align 4
  %90 = add nsw i32 %.01, %89
  br label %91

91:                                               ; preds = %86
  %92 = add nsw i32 %.0, 1
  br label %84, !llvm.loop !8

93:                                               ; preds = %84
  ret i32 %.01
}

; Function Attrs: mustprogress noinline norecurse ssp uwtable
define noundef i32 @main() #1 {
  %1 = call noundef i32 @_Z11test_passo1ii(i32 noundef 42, i32 noundef 24)
  %2 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %1)
  %3 = call noundef i32 @_Z11test_passo2i(i32 noundef 42)
  %4 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %3)
  %5 = call noundef i32 @_Z11test_passo3i(i32 noundef 42)
  %6 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %5)
  %7 = call noundef i32 @_Z13test_combinedii(i32 noundef 42, i32 noundef 24)
  %8 = call i32 (ptr, ...) @printf(ptr noundef @.str.3, i32 noundef %7)
  %9 = call noundef i32 @_Z16complex_functioniii(i32 noundef 42, i32 noundef 24, i32 noundef 10)
  %10 = call i32 (ptr, ...) @printf(ptr noundef @.str.4, i32 noundef %9)
  ret i32 0
}

declare i32 @printf(ptr noundef, ...) #2

attributes #0 = { mustprogress noinline nounwind ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 2]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Homebrew clang version 19.1.7"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
